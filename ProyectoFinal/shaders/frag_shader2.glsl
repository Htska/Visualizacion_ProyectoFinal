#version 410 core
// in vec3 fragColor;
in vec3 height;
out vec4 color;
uniform float m_max;
uniform float m_min;

void main()
{
    //float middle = (max+min)*0.5;

    //if (height.y < middle){
    //    float aspect = height.y/middle;
    //    color = vec4(aspect,aspect,1.0-aspect,1.0);
    //} else {
    //    float aspect = height.y/max;
    //    color = vec4(aspect,1.0-aspect,0.0,1.0);
    //}
    float value = (height.y -m_min) / (m_max -m_min);

    vec3 blue = vec3(0.0,0.0,1.0);
    vec3 yellow = vec3(1.0,1.0,0.0);
    vec3 red = vec3(1.0,0.0,0.0);

    //https://www.youtube.com/watch?v=7AQIdwd5PEU
    // Se utiliza el factor value*2.0 para que conforme avance el valor de la altura, entrgue el azul y cuando llega a 0.5 el amarillo
    // De igual manera se resta 0.5 para que ese valor esté entreo 0.5 *0.2, es decir entre 0 y uno
    if (value < 0.5){
        color = vec4(mix(blue,yellow,value*2.0),1.0);
    } else {
        color = vec4(mix(yellow,red,(value-0.5)*2.0),1.0);
    }
}
