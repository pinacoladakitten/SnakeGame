/**
 * ------Construct Main Objects-------
 */
var Keyboard  = Keyboard  || {};        // Keyboard Input
var SnakePlayer = SnakePlayer || {};    // Snake Players
var Board = Board || {};                // Board
var GameSys = GameSys || {};            // Game System


/**
 * ------Keyboard Map------
 */
Keyboard.Keymap1 = {37:'left', 38:'up', 39:'right', 40:'down'}; // Player 1 Keys
Keyboard.Keymap2 = {65:'left', 87:'up', 68:'right', 83:'down'}; // Player 2 Keys
Keyboard.Keymap3 = {74:'left', 73:'up', 76:'right', 75:'down'}; // Player 3 Keys
Keyboard.Keymap4 = {70:'left', 84:'up', 72:'right', 71:'down'}; // Player 4 Keys
/**
 * ------Keyboard Events------
 */
Keyboard.ControllerEvents = function() {
  
    // Set Vars
    var self      = this;
    this.pressKey = null;

    // Create 4 separate keymaps for each player(4)
    this.keymap1   = Keyboard.Keymap1; this.keymap2   = Keyboard.Keymap2;
    this.keymap3   = Keyboard.Keymap3; this.keymap4   = Keyboard.Keymap4;

    // Keydown Event
    document.onkeydown = function(event) {
        self.pressKey = event.which;
    };

    // Get Keys Pressed for each player (I wish I could simplify this :( )
    this.getKey1 = function() {return this.keymap1[this.pressKey];};
    this.getKey2 = function() {return this.keymap2[this.pressKey];};
    this.getKey3 = function() {return this.keymap3[this.pressKey];};
    this.getKey4 = function() {return this.keymap4[this.pressKey];};
};



/**
 * ------Board Class Stage (Handles Board Logic & and Executing Player Logic)------
 */
// arguments are: the canvas (in HTML) , config from GameSys, Keyboard Object
Board.Stage = function(canvas, conf, kb, playerCnt) {
    // Init Vars
    this.width     = canvas.width;      // Canvas Width
    this.height    = canvas.height;     // Canvas Height
    this.food      = {};                // Food object
    this.conf      = conf;              // Config from system
    this.kb        = kb;                // Keyboard obj (One object handles all input)
    this.playerCnt = playerCnt;                 // Player count (should move this to GameSys.conf)
    
    // Players array
    this.players = [];
    for(var i = 0; i < this.playerCnt; i++){
        var name = prompt("Enter your name for player "+(i+1)+": "); //Prompt for player's name before obj creation
        var Pl_obj = new SnakePlayer.Snake(this, i+1, name);
        this.players.push(Pl_obj);                      // Create player then push to array
    }
    
    // Create Food object
    this.initFood = function() {
        // Add food on stage at random location
        this.food = {
                x: Math.round(Math.random() * (this.width - conf.cw) / conf.cw),
                y: Math.round(Math.random() * (this.height - conf.cw) / conf.cw),
        };
    };

    // Init Food
    this.initFood();

    // ****Restart Stage when game over****
    this.restart = function() {
        var a = alert("GAME OVER");     // Alert (lazily)
        //Remember to uncomment, testing something for PHP purposes
        for(var i = 0; i < this.playerCnt; i++){
            document.getElementById("playerName").value += this.players[i].name.toString() + ",";
            document.getElementById("playerScore").value += this.players[i].score.toString() + ",";
        }
        
        document.getElementById("playerAmt").value = this.playerCnt.toString();
        document.getElementById("playerSet").value = "Set";
        document.getElementById("getPlayerInfo").submit();
        window.location.reload(true);  // Reload window (lazily)
    };
    
    // **------Main Gameplay Logic Elements (Game-loop)------**
    this.boardLogic = function() {
        for(var i = 0; i < this.playerCnt; ++i){    // For each player, update their movement and stuff
            
            for(var j = 0; j < this.playerCnt; ++j){ 
                for(var e = 0; e < this.players[j].length.length; e++){
                    if(this.players[i].nx == this.players[j].length[e].x && this.players[i].ny == this.players[j].length[e].y && this.players[j] != this.players[i]){this.restart();} // reset if hit tail
                }
            }
            
            this.players[i].snakeLogic();
        }
    }
    
};


/**
 * ------Snake Class------
 arguments are: the board, player number
 */
SnakePlayer.Snake = function(board, player, name) {
    // Set Score for player
    this.score = 0;
    // Set player tail size
    this.size = 1;
    // Set Direction
    this.direction = 'right';
    // Tail XY draw coords (actually array of sets{x,y})
    this.length    = [];
    this.name = name;
    // Player Colors
    switch(player){
        case 1: this.color = '#ff2d2e'; break; case 2: this.color = '#01fe00'; break;
        case 3: this.color = '#4c4dff'; break; case 4: this.color = '#ff902e'; break;
        default: this.color = '#fefcfd'; break;
    }
    
    
    // Add to length array based off of initial size
    for (var i = 0; i < this.size; i++) {     
      // Add Snake Cells
      this.length.push({x: i, y:0});
    }
    
    // Init Snake Position XY (random location)
    this.nx = Math.round(Math.random() * (board.width - board.conf.cw) / board.conf.cw);
    this.ny = Math.round(Math.random() * (board.height - board.conf.cw) / board.conf.cw);
    
    
    //-----**Main Game Logic (For game-loop)**------
    this.snakeLogic = function() {
        // Get Player Inputs
        var keyPress;
        switch(player) {
            // Check Keypress based off of player number
            case 1: keyPress = board.kb.getKey1(); break; case 2: keyPress = board.kb.getKey2(); break;
            case 3: keyPress = board.kb.getKey3(); break; case 4: keyPress = board.kb.getKey4(); break;
            default: keyPress = board.kb.getKey1(); break;
        }
        
        // Set player direction
        if (typeof(keyPress) != 'undefined') {
            // Only allow perpendicular movements
            // Left Right
            if(keyPress=='left' || keyPress=='right')
            {if(this.direction == 'up' || this.direction == 'down') this.direction = keyPress;}
            // Up Down
            if(keyPress=='up' || keyPress=='down')
            {if(this.direction == 'left' || this.direction == 'right') this.direction = keyPress;}
        }

        // Add position from direction input
        switch (this.direction) {
          case 'right': this.nx++;  break;
          case 'left':  this.nx--;  break;
          case 'up':    this.ny--;  break;
          case 'down':  this.ny++;  break;
        }
        
        // Logic of Snake reaching food
        if (this.nx == board.food.x && this.ny == board.food.y) {
            var tail = {x: this.nx, y: this.ny}; // Make tail at current position
            this.score++;
            board.initFood();
        } else {
            var tail = this.length.pop(); // Don't allow tail to increase
            tail.x   = this.nx;
            tail.y   = this.ny;
        }
        this.length.unshift(tail); // Add new tail to array
        
        // Board Looping Logic X
        if((this.nx * board.conf.cw) + 6 > board.width){this.nx = 0;}     // The 'board.conf.cw' scales our coords to the canvas
        if((this.nx * board.conf.cw) + 6 < 0){this.nx = board.width / board.conf.cw;}
        // Board Looping Logic Y
        if((this.ny * board.conf.cw) + 6 > board.height){this.ny = 0;}
        if((this.ny * board.conf.cw) + 6 < 0){this.ny = board.height / board.conf.cw;}
        
        // Collision with tails logic
        for(var e = 1; e < this.length.length; e++){
            if(this.nx == this.length[e].x && this.ny == this.length[e].y){board.restart();} // reset if hit tail
            //For multiple players it will need checks if running into another player's tail
            //That or it will require an array of the arrays where player's tails are being kept track of
            //Something like a double array?
        }
        
    };
};


// ------Game System------
// argument gets the canvas ID from HTML doc
GameSys.Setup = function(elementID, playerCnt){
     // Init Vars
    var canvas   = document.getElementById(elementID);  // Get canvas from doc
    var context  = canvas.getContext("2d");             // Get canvas context for drawing?
    
    // Config
    this.conf = {
        cw : 10,    // Scale to canvas I guess?
        fps  : 100  // Loops before update frame
    };
    
    // Create keyboard
    var kb = new Keyboard.ControllerEvents();
    
    // Create Board and (Board creates players)
    var board = new Board.Stage(canvas, this.conf, kb, playerCnt);
    
    // ------Main Drawing/Update logic-------
    this.drawStage = function() {
        // Draw Stage
        context.fillStyle = "#101010";
        context.fillRect(0, 0, board.width, board.height);  
        
        // Update All Movement
        board.boardLogic();
        
        
        // Draw Sneks and Scors
        for(var p = 0; p < board.playerCnt; p++)
        {
            // All Snek players
            for (var i = 0; i < board.players[p].length.length; i++) {
                var cell = board.players[p].length[i];
                this.drawCell(cell.x, cell.y, board.players[p].color); // draw each cell for each player with colors
            }
            
            // Draw Scores
            context.fillStyle = (board.players[p].color); // gets player color
            context.fillText('Score ' + (board.players[p].name) + ': ' + board.players[p].score, 5 + 100*p, ( board.height - 5));
        }

        // Draw Food
        this.drawCell(board.food.x, board.food.y, '#FFFFFF');
    };

        // Draw Cell Functions
    this.drawCell = function(x, y, color='rgb(170, 170, 170)') {
        context.fillStyle = color; // Sets color of drawing
        context.beginPath();
        context.arc((x * this.conf.cw + 6), (y * this.conf.cw + 6), 4, 0, 2*Math.PI, false); // draw circle
        context.fill();
    };
}

/**
 * Window Load (Executes right when window loads...so this goes first)
 */
window.onload = function() {
    //var frickyou = alert("FUCK");
    var invalid = true;
    var nameArr =[]; //Array for player names
    while(invalid){
      var playerCnt = prompt("Please enter the amount of players(up to 4 players, minimum 1 player): ", 1);
      if(isNaN(playerCnt)){
          alert("That is not a number");
          invalid = true;
      }
      else if(playerCnt > 4|| playerCnt < 1){
          alert("Invalid Number of Players");
          invalid = true;
      }
      else{
          alert("Setting up snake game with "+playerCnt+" players");
          invalid = false;
      }
    }
    var game = new GameSys.Setup('stage', playerCnt, nameArr);                      // setup game system
    setInterval(function() {game.drawStage();}, game.conf.fps); // loops the main logic based off of fps from config
};