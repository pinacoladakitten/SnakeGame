<?php
    class Highscores{
        private $con;
        
        public function __construct($con){
            $this->con = $con;
        }
        
        public function postScores() {
            if(isset($_POST['playerSet'])) {
                // Get the selected items through POST
                $playerArr = explode(",", $_POST['playerName']);
                $scoreArr = explode(",", $_POST['playerScore']);
                
                $playerAmt = $_POST['playerAmt'];
                
                for($i=0; $i<$playerAmt; $i++){
                    $result = mysqli_query($this->con, "INSERT INTO highscores VALUES ('', '$playerArr[$i]', '$scoreArr[$i]', '$playerAmt')");
                }
            }
        }
    }
?>