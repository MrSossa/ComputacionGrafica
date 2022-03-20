#include "colors.inc"
plane {
	y, -2
	pigment {checker Black, White}	
}

sphere {
    <-4,0,0>, 1
    pigment { Red }
    finish {
      ambient 1
      diffuse 0
      phong 0
      phong_size 10
    }
}

sphere {
    <-1.5,0,0>, 1
    pigment { Red }
    finish {
      ambient 0
      diffuse 1
      phong 0
      phong_size 10
    }
}

sphere {
    <1.5,0,0>, 1
    pigment { Red }
    finish {
      ambient 0
      diffuse 0
      phong 100
      phong_size 10
    }
}

sphere {
    <4,0,0>, 1
    pigment { Red }
    finish {
      ambient 0.2
      diffuse 1
      phong 0.03
      phong_size 3
    }
}
//povray glasschess.pov -w720 -h1080
/*
sphere {
    <-3,3,0>, 1
    pigment { White }
    finish {
      ambient 0.2
      diffuse 0.6
      phong 0.75
      phong_size 10
    }
}

sphere {
    <0,3,0>, 1
    pigment { White }
    finish {
      ambient 0.2
      diffuse 0.6
      phong .75
      phong_size 10
    }
}

sphere {
    <3,3,0>, 1
    pigment { White }
    finish {
      ambient 0.2
      diffuse 0.6
      phong .75
      phong_size 10
    }
}

sphere {
    <-3,6,0>, 1
    pigment { White }
    finish {
      ambient 0.2
      diffuse 0.6
      phong 0.75
      phong_size 10
    }
}

sphere {
    <0,6,0>, 1
    pigment { White }
    finish {
      ambient 0.2
      diffuse 0.6
      phong .75
      phong_size 10
    }
}

sphere {
    <3,6,0>, 1
    pigment { White }
    finish {
      ambient 0.2
      diffuse 0.6
      phong .75
      phong_size 10
    }
}

*/
light_source {
    <10, 10, -10>
    color White
}

camera {
	location <0, 3, -15>
	look_at <0, 3, 0>	
}