# Config File Spec

* Each line in the **config.txt** file specifies one of the config settings of the game.

## Window W H FL FS AL

W H
: width and height of window in `int` format

FL
: fps limit

FS
: whether the screen will be fullscreen. `0` or `1`

AL
: antialias level `int`

## Font F S R G B

F
: font file in `std::string` format

S
: font size in `int`

R G B
: (R, G, B) color code in `int` format


## Player SR CR S FR FG FB OR OG OB OT V

SR
: shape radius `int`

CR
: collision radius `int`

S
: speed `float`

FR FG FB
: fill color 

OR OG OB
: outline color

OT
: outline thickness `int`

V
: shape vertices `int`

## Enemy SR CR SMIN SMAX OR OG OB OT VMIN VMAX L SI

SR
: shape radius `int`

CR
: collision radius `int`

SMIN SMAX
: min max speed in `float`

OR OG OB
: outline color

OT
: outline thickness `int`

VMIN VMAX
: min max shape vertices in `int`

L
: lifespan of fission particles `int`

SI
: spawn interval `int`


## Bullet SR CR S FR FG FB OR OG OB OT V L

SR
: shape radius `int`

CR
: collision radius `int`

FR FG FB
: fill color 

OR OG OB
: outline color

OT
: outline thickness `int`

V
: shape vertices in `int`

L
: lifespan `int`

