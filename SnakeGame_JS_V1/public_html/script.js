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
Board.Stage = function(canvas, conf, kb) {
    // Init Vars
    this.width     = canvas.width;      // Canvas Width
    this.height    = canvas.height;     // Canvas Height
    this.food      = {};                // Food object
    this.conf      = conf;              // Config from system
    this.kb        = kb;                // Keyboard obj (One object handles all input)
    this.playerCnt = 1;                 // Player count (should move this to GameSys.conf)
    
    // Players array
    this.players = [];
    for(var i = 0; i < this.playerCnt; i++){
        var Pl_obj = new SnakePlayer.Snake(this, i+1);
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

    // Restart Stage when game over
    this.restart = function() {
        var a = alert("GAME OVER");     // Alert (lazily)
        window.location.reload(false);  // Reload window (lazily)
    };
    
    
    // **------Main Gameplay Logic Elements (Game-loop)------**
    this.boardLogic = function() {
        for(var i = 0; i < this.playerCnt; ++i){    // For each player, update their movement and stuff
            this.players[i].snakeLogic();
        }
    }
  
};


/**
 * ------Snake Class------
 arguments are: the board, player number
 */
SnakePlayer.Snake = function(board, player) {
    // Set Score for player
    this.score = 0;
    // Set player tail size
    this.size = 1;
    // Set Direction
    this.direction = 'right';
    // Tail XY draw coords (actually array of sets{x,y})
    this.length    = [];
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
    var nx = Math.round(Math.random() * (board.width - board.conf.cw) / board.conf.cw);
    var ny = Math.round(Math.random() * (board.height - board.conf.cw) / board.conf.cw);
    
    
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
          case 'right': nx++;  break;
          case 'left':  nx--;  break;
          case 'up':    ny--;  break;
          case 'down':  ny++;  break;
        }
        
        // Logic of Snake reaching food
        if (nx == board.food.x && ny == board.food.y) {
            var tail = {x: nx, y: ny}; // Make tail at current position
            this.score++;
            board.initFood();
        } else {
            var tail = this.length.pop(); // Don't allow tail to increase
            tail.x   = nx;
            tail.y   = ny;
        }
        this.length.unshift(tail); // Add new tail to array
        
        // Board Looping Logic X
        if((nx * board.conf.cw) + 6 > board.width){nx = 0;}     // The 'board.conf.cw' scales our coords to the canvas
        if((nx * board.conf.cw) + 6 < 0){nx = board.width / board.conf.cw;}
        // Board Looping Logic Y
        if((ny * board.conf.cw) + 6 > board.height){ny = 0;}
        if((ny * board.conf.cw) + 6 < 0){ny = board.height / board.conf.cw;}
        
        // Collision with tails logic
        for(var e = 1; e < this.length.length; e++){
            if(nx == this.length[e].x && ny == this.length[e].y){board.restart();} // reset if hit tail
        }
        
    }
};


// ------Game System------
// argument gets the canvas ID from HTML doc
GameSys.Setup = function(elementID){
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
    var board = new Board.Stage(canvas, this.conf, kb);
    
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
            context.fillText('Score P' + (p+1) + ': ' + board.players[p].score, 5 + 100*p, ( board.height - 5));
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
    var game = new GameSys.Setup('stage');                      // setup game system
    setInterval(function() {game.drawStage();}, game.conf.fps); // loops the main logic based off of fps from config
};