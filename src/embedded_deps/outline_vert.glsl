#version 140
in vec3 position;
in vec3 normal;
#ifdef S_VERTEX_COLOR
in vec4 color;
out vec4 vColor;
#endif
in vec4 uv;
out vec2 vUV;

uniform mat4 g_model;
uniform mat4 g_view;
uniform mat4 g_projection;

void main(void) {
    vec4 pos = vec4(position+normal*0.1,1.0); //THE NUMBER THAT IS MULTIPLIED HERE (0.1), IS THE SIZE OF THE OUTLINE, CHANGE IF WANTED
    gl_Position = g_projection * g_view * g_model * pos;
    vUV = uv.xy;
#ifdef S_VERTEX_COLOR
    vColor = color;
#endif
}
