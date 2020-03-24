function enter(context, dx, dy, sx, sy)
{
    context.save();
    context.translate(dx, dy);
    context.scale(sx, sy);
}

function leave(context, fs, ss, lw, lc)
{
    context.restore();
    context.fillStyle = fs;
    context.strokeStyle= ss;
    context.lineWidth = lw;
    context.lineCap = lc;
    context.stroke();
    context.fill();
}

function leaveWithoutFill(context, ss, lw, lc)
{
    context.restore();
    context.strokeStyle = ss;
    context.lineWidth = lw;
    context.lineCap = lc;
    context.stroke();
}

function leaveWithoutStroke(context, fs)
{
    context.restore();
    context.fillStyle = fs;
    context.fill();
}

function dpad(c)
{
    c.beginPath();
    c.moveTo(0.55, 0);
    c.lineTo(0.95, 0);
    c.quadraticCurveTo(1, 0, 1, 0.05);
    c.lineTo(1, 0.95);
    c.quadraticCurveTo(1, 1, 0.95, 1);
    c.lineTo(0.55, 1);
    c.quadraticCurveTo(0.5, 1, 0.5, 0.95);
    c.lineTo(0.5, 0.63);
    c.lineTo(0.012, 0.63);
    c.quadraticCurveTo(-0.12, 0.63, -0.105, 0.5);
    c.lineTo(-0.1, 0.4);
    c.quadraticCurveTo(-0.1, 0.35, 0.06, 0.35);
    c.lineTo(0.5, 0.35);
    c.lineTo(0.5, 0.05);
    c.quadraticCurveTo(0.5, 0, 0.55, 0);
    c.closePath();
}

function dpad_up_arrow(c)
{
    c.beginPath();
    c.arc(0.5, 0.5, 0.5, Math.PI, 2 * Math.PI)
    c.closePath();
}

function dpad_down_arrow(c)
{
    c.save();
    c.rotate(Math.PI);
    dpad_up_arrow(c);
    c.restore();
}

function dpad_left_arrow(c)
{
    c.save();
    c.rotate(1.5 * Math.PI);
    dpad_up_arrow(c);
    c.restore();
}

function dpad_center(c)
{
    c.beginPath();
    c.arc(0.5, 0.5, 0.45, 0, 2 * Math.PI);
    c.closePath();
}

function letter_g(c)
{   
    c.beginPath();
    c.arc(0.5, 0.5, 0.5, 0, 1.8 * Math.PI);
    c.moveTo(0.5, 0.5);
    c.lineTo(1, 0.5);
}

function letter_a(c)
{
    c.beginPath();
    c.moveTo(0.15, 0.85);
    c.lineTo(0.5, 0);
    c.moveTo(0.55, 0);
    c.lineTo(0.85, 0.85);
    c.moveTo(0.70, 0.6);
    c.lineTo(0.30, 0.6);
    c.moveTo(0.75, 0.6);
    c.lineTo(0.55, 0.2);
}

function letter_m(c)
{
    c.beginPath();
    c.moveTo(0.15, 0.85);
    c.lineTo(0.15, 0.15);
    c.moveTo(0.155, 0.15);
    c.lineTo(0.5, 0.5);
    c.moveTo(0.505, 0.5);
    c.lineTo(0.85, 0.15);
    c.moveTo(0.855, 0.15);
    c.lineTo(0.855, 0.85);
}

function letter_e(c)
{
    c.beginPath();
    c.moveTo(0.15, 0.15);
    c.lineTo(0.15, 0.85);
    c.moveTo(0.155, 0.85);
    c.lineTo(0.85, 0.85);
    c.moveTo(0.155, 0.5);
    c.lineTo(0.85, 0.5);
    c.moveTo(0.155, 0.15);
    c.lineTo(0.85, 0.15);
}

function letter_s(c)
{
    c.beginPath();
    c.arc(0.5, 0.30, 0.25, 0.65 * Math.PI, 1.80 * Math.PI);
    c.moveTo(0.40, 0.53);
    c.save();
    c.translate(0.75, 1.41);
    c.rotate(1.2 * Math.PI);
    c.arc(0.5, 0.30, 0.25, 0.5 * Math.PI, 1.70 * Math.PI);
    c.restore();
}

function dpad_right(c)
{
    c.beginPath();
    c.moveTo(0, 0);
    c.lineTo(0.85, 0);
    c.quadraticCurveTo(1, 0, 1, 0.15);
    c.lineTo(1, 0.85);
    c.quadraticCurveTo(1, 1, 0.85, 1);
    c.lineTo(0, 1);
    c.lineTo(0, 0);
    c.closePath();
}

function dpad_right_arrow(c)
{
    c.beginPath();
    c.arc(0.5, 0.5, 0.5, 1.5 * Math.PI, 0.5 * Math.PI);
    c.closePath();
}

function letter_o(c)
{
    c.beginPath();
    c.arc(0.5, 0.5, 0.45, 0, 2 * Math.PI);
}

function letter_n(c)
{
    c.beginPath();
    c.moveTo(0.15, 0.85);
    c.lineTo(0.15, 0.15);
    c.moveTo(0.155, 0.15);
    c.lineTo(0.85, 0.85);
    c.moveTo(0.855, 0.85);
    c.lineTo(0.855, 0.15);
}

function letter_q(c)
{
    c.beginPath();
    c.arc(0.5, 0.5, 0.45, 0, 2 * Math.PI);
    c.moveTo(0.5, 0.5);
    c.lineTo(1, 1);
}

function letter_u(c)
{
    c.beginPath();
    c.moveTo(0.20, 0);
    c.lineTo(0.20, 0.5);
    c.moveTo(0.80, 0);
    c.lineTo(0.80, 0.5);
    c.arc(0.5, 0.5, 0.30, 0, Math.PI);
}

function letter_i(c)
{
    c.beginPath();
    c.moveTo(0.5, 0);
    c.lineTo(0.5, 1);
}

function letter_c(c)
{
    c.beginPath();
    c.arc(0.5, 0.5, 0.5, 0.25 * Math.PI, 1.75 * Math.PI);
}

function letter_k(c)
{
    c.beginPath();
    c.moveTo(0.15, 0.15);
    c.lineTo(0.15, 0.85);
    c.moveTo(0.25, 0.5);
    c.lineTo(0.85, 0.15);
    c.moveTo(0.25, 0.5);
    c.lineTo(0.85, 0.85);
}

function main() 
{
    var c2d = document.getElementById("acanvas").getContext("2d");
    
    c2d.save();
    c2d.translate(-580, -270);

    c2d.fillStyle = "#0DA1AD";
    enter(c2d, 550, 300, 1, 1);
        c2d.fillRect(0, 0, 618, 340);
    leave(c2d, "#0DA1AD", "black");

    enter(c2d, 628, 362, 1920/15, 1080/4.70);
    dpad(c2d);
    leaveWithoutStroke(c2d, "#024651");

    enter(c2d, 706, 385, 1920/53, 1080/24);
    dpad_up_arrow(c2d);
    leaveWithoutStroke(c2d, "#198794");

    enter(c2d, 742, 568, 1920/53, 1080/24);
    dpad_down_arrow(c2d);
    leaveWithoutStroke(c2d, "#198794");

    enter(c2d, 640, 492, 1920/44, 1080/32);
    dpad_left_arrow(c2d);
    leaveWithoutStroke(c2d, "#198794");

    enter(c2d, 703, 455, 1920/48, 1080/28);
    dpad_center(c2d);
    leaveWithoutStroke(c2d, "#198794")

    enter(c2d, 775, 370, 1920/30, 1080/17);
    letter_g(c2d);
    leaveWithoutFill(c2d, "black", 15, "round");

    enter(c2d, 845, 370, 1920/27, 1080/15);
    letter_a(c2d);
    leave(c2d, "null", "black", 15, "round");

    enter(c2d, 920, 355, 1920/25, 1080/12);
    letter_m(c2d);
    leave(c2d, "null", "black", 15, "round");

    enter(c2d, 1000, 355, 1920/30, 1080/12);
    letter_e(c2d);
    leave(c2d, "null", "black", 15, "round");

    enter(c2d, 1060, 365, 1920/25, 1080/18);
    letter_s(c2d);
    leaveWithoutFill(c2d, "black", 15, "round"); 

    enter(c2d, 848, 450, 1920/30, 1080/17);
    letter_o(c2d);
    leaveWithoutFill(c2d, "black", 15, "round");

    enter(c2d, 920, 438, 1920/25, 1080/12);
    letter_n(c2d);
    leave(c2d, "null", "black", 15, "round");

    enter(c2d, 1000, 438, 1920/30, 1080/12);
    letter_e(c2d);
    leave(c2d, "null", "black", 15, "round");

    enter(c2d, 775, 522, 1920/30, 1080/17);
    letter_q(c2d);
    leaveWithoutFill(c2d, "black", 15, "round");

    enter(c2d, 842, 530, 1920/27, 1080/15);
    letter_u(c2d);
    leaveWithoutFill(c2d, "black", 15, "round");

    enter(c2d, 880, 530, 1920/25, 1080/19);
    letter_i(c2d);
    leave(c2d, "null", "black", 15, "round");

    enter(c2d, 936, 530, 1920/31, 1080/19);
    letter_c(c2d);
    leaveWithoutFill(c2d, "black", 15, "round");

    enter(c2d, 1000, 520, 1920/30, 1080/14);
    letter_k(c2d);
    leave(c2d, "null", "black", 15, "round");

    enter(c2d, 777, 454, 1920/36, 1080/21);
    dpad_right(c2d);
    leave(c2d, "black", "black", 15, "round");

    enter(c2d, 777, 462, 1920/44, 1080/32);
    dpad_right_arrow(c2d);
    leave(c2d, "#198794", "null", 1, "round");

    c2d.restore();
}