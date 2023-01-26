<?php
    include 'header.php';
    $total_pages = mysqli_query($link, "SELECT * FROM mq_sensors")->num_rows;
    $page = isset($_GET['page']) && is_numeric($_GET['page']) ? $_GET['page'] : 1;
    $limit = 10;
?>


<?php
    include 'footer.php';
?>