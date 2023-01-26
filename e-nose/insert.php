<?php

require_once 'connection.php';

if ($_SERVER['REQUEST_METHOD'] == 'POST') {

    try {
        $data = json_decode(file_get_contents('php://input'), true);
        $mq4 = $data['mq4'];
        $mq136 = $data['mq136'];
        $mq137 = $data['mq137'];
        $created_at = date('Y-m-d H:i:s');

        $sql = "INSERT INTO mq_sensors (mq4, mq136, mq137, created_at) VALUES ('$mq4', '$mq136', '$mq137', '$created_at')";

        if (mysqli_query($link, $sql)) {
            http_response_code(201);
            $response = array(
                'data' => array(
                    'mq4' => $mq4,
                    'mq136' => $mq136,
                    'mq137' => $mq137,
                    'created_at' => $created_at
                ),
                'status_message' => 'Data berhasil ditambahkan.'
            );
        } else {
            http_response_code(422);
            $response = array(
                'data' => array(),
                'status_message' => 'Data gagal ditambahkan.',
                'error' => mysqli_error($link)
            );
        }
    } catch (Exception $e) {
        http_response_code(500);
        $response = array(
            'data' => array(),
            'status_message' => 'Terjadi error pada server.'
        );
    }

    header('Content-Type: application/json');
    echo json_encode($response);
}