// let x;
// let y;

// function setup() {
//   createCanvas(400, 400);
//   x = width / 2;
//   y = height / 2;
// }

// function draw() {
//   background(0, 220, 0);
//   fill(100, 123, 255);
//   ellipse(x, y, 50, 50);
// }

let b1_color = 255;

let b1_x;
let b1_y;
let b1_radius = 25;

let b1_Speed;
let b1_angle;
let b1_xSpeed;
let b1_ySpeed;

let b2_x;
let b2_y;
let b2_radius = 50;

let b2_Speed;
let b2_angle;
let b2_xSpeed;
let b2_ySpeed;

function setup() {
  createCanvas(400, 400);
  b1_x = width / 3;
  b1_y = height / 3;
  
  b1_Speed = 5;
  b1_angle = random(1,10);
  b1_xSpeed = b1_Speed * cos(b1_angle);
  b1_ySpeed = b1_Speed * sin(b1_angle);
  
  b2_x = 2 * width / 3;
  b2_y = 2 * height / 3;
	
  b2_Speed = 1;
  b2_angle = random(1,10);
  b2_xSpeed = b1_Speed * cos(b2_angle);
  b2_ySpeed = b1_Speed * sin(b2_angle);
}

function balls_dist(x1, y1, x2, y2)
{
  return (sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)));
}



function draw() {
  background(220);
  fill(100, 123, b1_color);
  ellipse(b1_x, b1_y, b1_radius * 2, b1_radius * 2);
  
  b1_x += b1_xSpeed;
  b1_y += b1_ySpeed;
  
  if (b1_x > width - b1_radius || b1_x < b1_radius) {
  	// if (xSpeed > 0)
  	// xSpeed++;
  	// else
  	// xSpeed--;
    b1_xSpeed = -b1_xSpeed;
  } 
  
  if (b1_y > height - b1_radius || b1_y < b1_radius) {
    b1_ySpeed = -b1_ySpeed;
  }
  
  if (balls_dist(b1_x, b1_y, b2_x, b2_y) < b1_radius + b2_radius
      && !(b1_x > width - b1_radius || b1_x < b1_radius)
      && !(b1_y > height - b1_radius || b1_y < b1_radius))
  {
    b1_xSpeed = (b1_x - b2_x) / balls_dist(b1_x, b1_y, b2_x, b2_y) * b1_Speed;
    b1_ySpeed = (b1_y - b2_y) / balls_dist(b1_x, b1_y, b2_x, b2_y) * b1_Speed;
  }
  
  fill(255, 123, 100);
  ellipse(b2_x, b2_y, b2_radius * 2, b2_radius * 2);
  
  b2_x += b2_xSpeed;
  b2_y += b2_ySpeed;
  
  if (b2_x > width - b2_radius || b2_x < b2_radius) {
    b2_xSpeed = -b2_xSpeed;     //bounce
    // b2_x = (b2_x+width)%width;  //go through
  } 
  
  if (b2_y > height - b2_radius || b2_y < b2_radius) {
    b2_ySpeed = -b2_ySpeed;      //bounce
    // b2_y = (b2_y+height)%height; //go through
  }
  
  if (balls_dist(b1_x, b1_y, b2_x, b2_y) < b1_radius + b2_radius
      && !(b2_x > width - b2_radius || b2_x < b2_radius)
      && !(b2_y > height - b2_radius || b2_y < b2_radius))
  {
    b2_xSpeed = (b2_x - b1_x) / balls_dist(b1_x, b1_y, b2_x, b2_y) * b2_Speed;
    b2_ySpeed = (b2_y - b1_y) / balls_dist(b1_x, b1_y, b2_x, b2_y) * b2_Speed;
  }
}
