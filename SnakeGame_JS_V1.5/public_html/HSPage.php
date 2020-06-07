<?php
    include("classes/config.php");
    include("classes/highscores.php");

    $highscores = new Highscores($con);
?>

<head>
  <meta charset="UTF-8">
  <title>Snake Game</title>
  <link rel="stylesheet" href="./style.css">

</head>
<body>
<h3>Highscores</h3>
    <?php
        if(isset($_POST['playerSet'])) {
            $highscores->postScores();
        }
        
        $result = mysqli_query($con, "SELECT * FROM highscores ORDER BY score DESC");
        echo "<table>
                    <div class='gridViewScores'>
                        <tr>
                            <th>Player</th>
                            <th>Score</th>
                            <th>Player Amount</th> 
                        </tr>";
        while($printRes = mysqli_fetch_array($result)){
            echo "<tr>
                    <td> ".$printRes['playerName']."</td>
                    <td> ".$printRes['score']."</td>
                    <td> ".$printRes['playerAmount']."</td>
                    </tr>";
        }
        echo "</div>
            </table>";
    ?>
    <form id="replayStuff" action="index.php">
        <div class='playerAgainButton'>
            <button id= "playAgain" type="submit" name="playAgain">PLAY AGAIN?</button>
        </div>
    </form>

</body>
</html>