<?php
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");

if (!isset($_POST["map"]) || empty($_POST["map"])) {
    echo "No map data";
    http_response_code(400);
    exit;
}

$_POST["map"] = str_replace("\r", "\n", $_POST["map"]);
$_POST["map"] = str_replace("\n\n", "\n", $_POST["map"]);

if (!preg_match("/^[0-9]+\n((##(start|end)|\w+ 0 0)\n)+((\w+-\w+)\n)+$/", $_POST["map"])) {
    echo "Invalid map data";
    http_response_code(400);
    exit;
}

exec("echo '".$_POST["map"]."' | pathfinding/pathfinding", $output);

$moves = array_slice($output, array_search("#moves", $output) + 1);

$current_positions = array_fill(0, 100, 1);
$result = [];
foreach ($moves as $k=>$move) {
    $move = explode(" ", $move);
    $result[$k] = [];
    foreach ($move as $step) {
        $step = explode("-", $step);
        $ant_id = intval(substr($step[0], 1)) - 1;
        $result[$k][] = [$current_positions[$ant_id], intval($step[1])];
        $current_positions[$ant_id] = intval($step[1]);
    }
}

echo json_encode($result);