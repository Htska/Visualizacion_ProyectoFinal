#version 410 core
in vec3 fragColor;
uniform float grad_length;
out vec4 color;

vec3 c(float f){
    float dx = 0.8;
    f = clamp(f,0.0,1.0);
    float g = (6-2*dx)*f+dx;
    float r = max(0,(3-abs(g-4)-abs(g-5))/2);
    float gr = max(0,(4-abs(g-2)-abs(g-4))/2);
    float b = max(0,(3-abs(g-1)-abs(g-2))/2);
    return vec3(r,gr,b);
}

void main()
{
    color = vec4(c(grad_length), 1.0);
}