<!DOCTYPE html>
<html lang="en" >
<?php
    include("classes/config.php");
    include("classes/highscores.php");
?>

<head>
  <meta charset="UTF-8">
  <title>Snake Game</title>
  <link rel="stylesheet" href="./style.css">

</head>
<body>
<!-- partial:index.partial.html -->
<h3>Simple Snek Game</h3>
<canvas id="stage" height="400" width="520"></canvas>
<!-- partial -->
    
    <script  src="./script.js"></script>
    <form id="getPlayerInfo" action="HSPage.php" method="POST">
        <input type="hidden" id="playerName" name="playerName">
        <input type="hidden" id="playerScore" name="playerScore">
        <input type="hidden" id="playerAmt" name="playerAmt">
        <input type="hidden" id="playerSet" name="playerSet">
    </form>

</body>
</html>