#type vertex
#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 a_Tangent;
layout (location = 4) in vec3 a_Bitangent;




out vec3 v_Position;
out vec3 v_Color;
out vec2 UV;


uniform mat4 u_ViewProjection;
uniform vec3 u_Color;

void main()
{
   v_Position = aPos;
   UV = aUV;
   v_Color =  u_Color;
   gl_Position = u_ViewProjection * vec4(aPos * 5.0, 1.0);
};



#type fragment
#version 420 core

layout (binding = 0) uniform sampler2D diffuse; 
layout (binding = 1) uniform sampler2D specular; 
layout (binding = 2) uniform sampler2D normal;
layout (binding = 2) uniform sampler2D height;

out vec4 FragColor;

in vec3 v_Position;
in vec3 v_Color;
in vec2 UV;


float caculateEdge(float value, float edge, vec2 uv, float num)
{
    vec2 newUV = uv * num;
	vec2 fracUV = fract(newUV);
	vec2 gedge = smoothstep(value,edge+value,(1.0 - abs(1.0 - fracUV * 2.0))*0.5);
	float edges = max(gedge.x,gedge.y);
    return edges;
}


void main()
{
	vec3 pos = v_Position;

   float BigEdge = caculateEdge(0.48,0.4,UV,10);
   float SmallEdge = caculateEdge(0.48,0.4,UV,100);
   float FinalAlpha = BigEdge + SmallEdge*0.5;

	vec4 color = texture(diffuse, UV);
	FragColor = vec4(vec3(1) ,FinalAlpha*10.0);
};