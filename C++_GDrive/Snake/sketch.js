var s;
var scl = 20;

function Setup(){
	createCanvas(600, 600);
	s = new Snake();
	frameRate(10);
	PickLocation();
}

function PickLocation(){
	var cols = floor(width/scl);
	var rows = floor(height/scl);
	food = createVector(floor(random(cols)), floor(random(rows)));
	food.mult(scl);
}

function mousePressed(){
	s.total++;
	
}

function draw(){
	background(51);
	
	if(s.eat(food)){
		PickLocation();
	}

	s.death();
	s.update();
	s.show();

	fill(255,0,100);
	rect.(food.x, food.y, scl, scl);
}

function keyPressed() {
	if(keyCode === UP_ARROW)
		s.dir(0,-1);
	else if(keyCode === DOWN_ARROW)
		s.dir(0,1);
	else if(keyCode === RIGHT_ARROW)
		s.dir(1,0);
	else if(keyCode === LEFT_ARROW)
		s.dir(-1, 0);
}
