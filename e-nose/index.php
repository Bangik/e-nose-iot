<?php
    include 'header.php';
    $total_pages = mysqli_query($link, "SELECT * FROM mq_sensors")->num_rows;
    $page = isset($_GET['page']) && is_numeric($_GET['page']) ? $_GET['page'] : 1;
    $limit = 10;
?>
<main role="main" class="col-md-9 ml-sm-auto col-lg-10 px-md-4">
    <div class="pt-3 pb-2 mb-3 border-bottom">
        <h1 class="h2">Data Sensor</h1>
        <div class="table-responsive pt-3 pb-2 mb-3 border-bottom">
            <table class="table table-striped table-sm" id="myTable">
                <thead>
                    <tr>
                        <th>#</th>
                        <th>Metana (MQ4)</th>
                        <th>H2S (MQ136)</th>
                        <th>Amonia (MQ137)</th>
                        <th>Waktu</th>
                    </tr>
                </thead>
                <tbody>
                    <?php 
                        if($stmt = $link->prepare('SELECT * FROM mq_sensors ORDER BY id DESC LIMIT ?,?')){
                            $stmt->bind_param('ii', $start, $limit);
                            $start = ($page - 1) * $limit;
                            $stmt->execute();
                            $result = $stmt->get_result();
                        $no = 1;
                        while($row = $result->fetch_assoc()){
                    ?>
                    <tr>
                        <td><?php echo $no++; ?></td>
                        <td><?php echo $row['mq4']; ?></td>
                        <td><?php echo $row['mq136']; ?></td>
                        <td><?php echo $row['mq137']; ?></td>
                        <td><?php echo $row['created_at']; ?></td>
                    </tr>
                    <?php } 
                    }
                    ?>
                </tbody>
            </table>
            <nav aria-label="Page navigation example">
                <ul class="pagination">
                    <li class="page-item <?php if($page <= 1){ echo 'disabled'; } ?>">
                        <a class="page-link" href="index.php?page=<?php echo $page - 1 ?>" tabindex="-1">Previous</a>
                    </li>
                    <?php 
                        $total_page = ceil($total_pages / $limit);
                        $start_number = ($page > 3) ? $page - 3 : 1;
                        $end_number = ($page < $total_page - 3) ? $page + 3 : $total_page;
                        for($i = $start_number; $i <= $end_number; $i++){
                            $active = ($page == $i) ? 'active' : '';
                    ?>
                    <li class="page-item <?php echo $active; ?>"><a class="page-link" href="index.php?page=<?php echo $i; ?>"><?php echo $i; ?></a></li>
                    <?php } ?>
                    <li class="page-item
                    <?php if($page >= $total_page){ echo 'disabled'; } ?>">
                        <a class="page-link" href="index.php?page=<?php echo $page + 1 ?>">Next</a>
                    </li>
                </ul>
            </nav>
        </div>
    </div>
  
  	<div class="pt-3 pb-2 mb-3 border-bottom">
        <h1 class="h2">Chart</h1>
    </div>
    <canvas class="my-4 w-100" id="myChart" width="900" height="380"></canvas>
</main>

<?php
    include 'footer.php';
?>