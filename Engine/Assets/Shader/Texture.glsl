#type vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aCol;
layout (location = 2) in vec2 aUV;

out vec3 v_Position;
out vec4 v_Color;
out vec2 v_UV;

uniform mat4 u_ViewProjection;
uniform vec3 u_Color;

void main()
{
   v_Position = aPos;
   v_UV = aUV;
   v_Color =  aCol * vec4(u_Color,1.0);
   gl_Position = u_ViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
};



#type fragment
#version 330 core

out vec4 FragColor;

in vec3 v_Position;
in vec4 v_Color;
in vec2 v_UV;

uniform sampler2D u_Texture;

void main()
{
	vec4 color = texture(u_Texture, v_UV);
	FragColor = vec4(color);
};