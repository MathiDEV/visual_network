var bgc = document.createElement("canvas");
var bg = bgc.getContext("2d");
var dd = document.createElement("canvas");
var cv = dd.getContext("2d");
var w, h;
const move_iterations = 100;
var move_dots = false, iterations = 0;
var grid = {
    shapeSideSize: 30,
    shapeSides: 6,
    shapeApothem: 30 * Math.sqrt(3) / 2,
};
var start_icon = new Image();
start_icon.src = "assets/img/start.png";
var end_icon = new Image();
end_icon.src = "assets/img/end.png";
var solve_steps = [];
var solve_index = 0;
var solve_button = document.getElementById("solve"),
stop_button = document.getElementById("stop");


var user_gui = {
    mouse: [0, 0],
    hover: [0, 0],
    active: [-1, -1],
    cases: [],
    links: [],
    actives: [],
    dots: [],
};

bgc.style.position = dd.style.position = "fixed";

document.body.appendChild(bgc);
document.body.appendChild(dd);

function sameCoords(a, b) {
    return a[0] == b[0] && a[1] == b[1];
}

function polygon(coords, ns, s) {
    this.shape = new Path2D();
    this.shape.moveTo(coords[0] + s * Math.cos(0), coords[1] + s * Math.sin(0));
    for (var i = 1; i <= ns; i++) {
        this.shape.lineTo(coords[0] + s * Math.cos(i * 2 * Math.PI / ns), coords[1] + s * Math.sin(i * 2 * Math.PI / ns));
    }
    return this.shape;
}

function coordToCase(x, y) {
    for (i = 0; i < user_gui.cases.length; i++) {
        if (sameCoords(user_gui.cases[i].coordinates, [x, y])) {
            return i;
        }
    }
    return -1;
}

function coordsToLink(from, to) {
    for (i = 0; i < user_gui.links.length; i++) {
        if (sameCoords(user_gui.links[i].from, from) && sameCoords(user_gui.links[i].to, to)
            || sameCoords(user_gui.links[i].from, to) && sameCoords(user_gui.links[i].to, from)) {
            return i;
        }
    }
    return -1;
}

function removeArrayIndex(array, index) {
    return array.slice(0, index).concat(array.slice(index + 1));
}

function toggleCase(x, y) {
    if ((index = coordToCase(x, y)) != -1) {
        if (user_gui.cases[index].type != undefined)
            return
        user_gui.cases[index].opacity_dir = -1;
        unlinkCoords([x, y]);
        user_gui.active = [-1, -1];
        return;
    }
    user_gui.cases.push({ coordinates: [x, y], opacity: 0, opacity_dir: 1 });
}

function unlinkCoords(coords) {
    for (i = 0; i < user_gui.links.length; i++) {
        if (sameCoords(user_gui.links[i].from, coords) || sameCoords(user_gui.links[i].to, coords)) {
            user_gui.links = removeArrayIndex(user_gui.links, i);
            i--;
        }
    }
}

function toggleLink(from, to) {
    if ((index = coordsToLink(from, to)) != -1) {
        user_gui.links[index].opacity_dir = -1;
        return;
    }
    user_gui.links.push({ from: from, to: to, opacity: 0, opacity_dir: 1 });
}

function indexsToCoords(c, d) {
    var ty = d * grid.shapeApothem * 2.2 + (c % 2) * grid.shapeSideSize;
    var tx = c * grid.shapeSideSize * 1.7;
    return [tx, ty];
}

function mouseHover(index) {
    var coords = indexsToCoords(index[0], index[1]);

    if (user_gui.mouse[0] >= coords[0] - grid.shapeSideSize * 0.7
        && user_gui.mouse[0] <= coords[0] + grid.shapeSideSize * 0.8
        && user_gui.mouse[1] >= coords[1] - grid.shapeSideSize * 0.9
        && user_gui.mouse[1] <= coords[1] + grid.shapeSideSize * 0.85) {
        user_gui.hover = index;
    }
}

function drawLink(from, to) {
    cv.lineWidth = 5;
    cv.strokeStyle = '#228fc9' + opacityToHex(user_gui.links[i].opacity);
    var fc = indexsToCoords(from[0], from[1]);
    var tc = indexsToCoords(to[0], to[1]);
    cv.beginPath();
    cv.moveTo(fc[0], fc[1]);
    cv.lineTo(tc[0], tc[1]);
    cv.stroke();
}

function draw_background() {
    bg.clearRect(0, 0, w, h);
    bg.fillStyle = '#ebebeb';
    for (var c = 0; c < grid.width; c++) {
        for (var d = 0; d < grid.height; d++) {
            var coords = indexsToCoords(c, d);
            let mesh = [];
            mesh.push(new polygon(coords, grid.shapeSides, grid.shapeSideSize));
            bg.fill(mesh[0]);
        }
    }
}

function opacityToHex(opacity) {
    var hex = Math.round(opacity * 255).toString(16);
    if (hex.length == 1) {
        hex = "0" + hex;
    }
    return hex;
}

function sendDot(from, to) {
    user_gui.dots.push({ from: from, to: to, current: [...from] });
}

function draw() {
    user_gui.hover = [-1, -1];
    if (!move_dots)
        for (var c = 0; c < grid.width; c++)
            for (var d = 0; d < grid.height; d++)
                mouseHover([c, d], coords);

    cv.clearRect(0, 0, w, h);

    for (i = 0; i < user_gui.links.length; i++) {
        drawLink(user_gui.links[i].from, user_gui.links[i].to);
    }
    for (i = 0; i < user_gui.dots.length; i++) {
        cv.beginPath();
        cv.arc(user_gui.dots[i].current[0], user_gui.dots[i].current[1], grid.shapeSideSize * 0.3, 0, 2 * Math.PI);
        cv.fillStyle = '#228fc9';
        cv.fill();
    }
    for (i = 0; i < user_gui.cases.length; i++) {
        cv.fillStyle = '#3eb2f0' + opacityToHex(user_gui.cases[i].opacity);
        var coords = indexsToCoords(...user_gui.cases[i].coordinates);
        let mesh = [];
        mesh.push(new polygon(coords, grid.shapeSides, grid.shapeSideSize));
        cv.fill(mesh[0]);
        if (user_gui.cases[i].type != undefined) {
            cv.drawImage((user_gui.cases[i].type == "start" ? start_icon : end_icon), coords[0] - 12, coords[1] - 12, grid.shapeSideSize * 0.8, grid.shapeSideSize * 0.8);
        }
    }
    if (!move_dots && user_gui.hover[0] != -1) {
        cv.strokeStyle = "#ffffff"
        cv.lineWidth = 2;
        coords = indexsToCoords(...user_gui.hover);
        let mesh = [];
        mesh.push(new polygon(coords, grid.shapeSides, grid.shapeSideSize));
        cv.stroke(mesh[0]);
    }
    if (!move_dots && user_gui.active[0] != -1) {
        cv.lineWidth = 3;
        cv.strokeStyle = "#228fc9"
        coords = indexsToCoords(...user_gui.active);
        let mesh = [];
        mesh.push(new polygon(coords, grid.shapeSides, grid.shapeSideSize));
        cv.stroke(mesh[0]);
    }
}

var reset = function () {
    w = bgc.width = dd.width = window.innerWidth;
    h = bgc.height = dd.height = window.innerHeight;
    grid.width = Math.ceil(w / (grid.shapeSideSize * 1.7));
    grid.height = Math.ceil(h / (grid.shapeApothem * 2.2));
    draw_background()
    draw();
}
reset();
user_gui.cases = [
    { coordinates: [3, Math.floor(grid.height / 2) - 1], opacity: 1, opacity_dir: 1, type: "start" },
    { coordinates: [Math.floor(grid.width - 3 + (grid.width % 2)), Math.floor(grid.height / 2) - 1], opacity: 1, opacity_dir: 1, type: "end" }
];

function manage_opacities(array_name) {
    for (i = 0; i < user_gui[array_name].length; i++) {
        user_gui[array_name][i].opacity += user_gui[array_name][i].opacity_dir * 0.3;
        if (user_gui[array_name][i].opacity_dir == 1)
            user_gui[array_name][i].opacity = Math.min(user_gui[array_name][i].opacity, 1);
        else
            user_gui[array_name][i].opacity = Math.max(user_gui[array_name][i].opacity, 0);
        if (user_gui[array_name][i].opacity_dir == -1 && user_gui[array_name][i].opacity == 0) {
            user_gui[array_name] = removeArrayIndex(user_gui[array_name], i);
        }
    }
}

function getMap(nb) {
    map = nb + "\n";
    for (i in user_gui.cases) {
        let node = user_gui.cases[i];
        if (node.type != undefined) {
            map += "##" + node.type + "\n";
        }
        map += (parseInt(i) + 1) + " 0 0\n"
    }
    for (link of user_gui.links) {
        from = coordToCase(...link.from);
        to = coordToCase(...link.to);
        map += (from + 1) + "-" + (to + 1) + "\n";
    }
    return map;
}

function nextMoves() {
    if (solve_index >= solve_steps.length) {
        solve_button.style.display = "block";
        stop_button.style.display = "none";
        solve_index = 0;
        solve_steps = [];
        return;
    }
    let current_move = solve_steps[solve_index];
    for (step of current_move) {
        let from = indexsToCoords(...user_gui.cases[step[0] - 1].coordinates),
            to = indexsToCoords(...user_gui.cases[step[1] - 1].coordinates);
        sendDot(from, to);
    }
    solve_index++;
    move_dots = true;
}

function solve(nb) {
    var xhr = new XMLHttpRequest();
    xhr.open("POST", "http://localhost:8001/api", true);
    var formdata = new FormData();
    formdata.append("map", getMap(nb));
    xhr.send(formdata);
    xhr.onreadystatechange = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
            solve_steps = JSON.parse(xhr.responseText);
            solve_index = 0;
            nextMoves();
        }
    }
}
setInterval(function () {
    manage_opacities("cases");
    manage_opacities("links");
    if (move_dots) {
        for (i = 0; i < user_gui.dots.length; i++) {
            user_gui.dots[i].current[0] += (user_gui.dots[i].to[0] - user_gui.dots[i].from[0]) / move_iterations;
            user_gui.dots[i].current[1] += (user_gui.dots[i].to[1] - user_gui.dots[i].from[1]) / move_iterations;
            if (sameCoords(user_gui.dots[i].current, user_gui.dots[i].to)) {
                user_gui.dots = removeArrayIndex(user_gui.dots, i);
            }
        }
        iterations++;
        if (iterations == move_iterations) {
            user_gui.dots = [];
            move_dots = false;
            iterations = 0;
            nextMoves();
        }
    }
    draw();
}, 20);


window.addEventListener("resize", reset);
dd.addEventListener("mousemove", function (e) {
    user_gui.mouse = [e.clientX, e.clientY];
});
dd.addEventListener("dblclick", function (e) {
    if (e.shiftKey)
        return;
    if (user_gui.hover[0] != -1) {
        toggleCase(user_gui.active[0], user_gui.active[1]);
    }
});

dd.addEventListener("click", function (e) {
    if (user_gui.hover[0] != -1) {
        if (user_gui.active[0] != -1
            && !sameCoords(user_gui.active, user_gui.hover)
            && coordToCase(user_gui.active[0], user_gui.active[1]) != -1
            && coordToCase(user_gui.hover[0], user_gui.hover[1]) != -1)
            if (e.shiftKey) {
                toggleLink(user_gui.active, user_gui.hover);
            }
        user_gui.active = user_gui.hover;
    }
});

stop_button.style.display = "none";
solve_button.addEventListener("click", function () {
    if (move_dots)
        return;
    if (!document.getElementById("number_form").reportValidity())
        return;
    this.style.display = "none";
    stop_button.style.display = "block";
    let nb = parseInt(document.getElementById("number").value);
    solve(nb);
});

stop_button.addEventListener("click", function () {
    if (!move_dots)
        return;
    this.style.display = "none";
    solve_button.style.display = "block";
    move_dots = false;
    iterations = 0;
    solve_index = 0;
    user_gui.dots = [];
    solve_steps = [];
});