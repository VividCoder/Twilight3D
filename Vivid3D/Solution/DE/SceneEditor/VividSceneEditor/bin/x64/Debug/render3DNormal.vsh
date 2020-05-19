cbuffer Constants
{
    float4x4 g_View;
    float4x4 g_Model;
    float4x4 g_Projection;
    float4x4 g_World;
    float4 lightDir;
    float4 lightPos;
    float4 lightDiff;
    float4 lightSpec;
    float4 camPos;
};

// Vertex shader takes two inputs: vertex position and color.
// By convention, Diligent Engine expects vertex shader inputs to be 
// labeled 'ATTRIBn', where n is the attribute number.
struct VSInput
{
    float3 Pos   : ATTRIB0;
    float3 UV    : ATTRIB1;
	float3 Normal : ATTRIB2;
	float3 Tangent : ATTRIB3;
	float3 BiNormal : ATTRIB4;
}
;

struct PSInput 
{ 
    float4 Pos   : SV_POSITION; 
    float3 UV : TEX_COORD;
	float3 Normal : NORMAL;
	float3 Tangent : TANGENT;
    float3 lightDiff : LIGHT_DIFF;
    float3 lightSpec : LIGHT_SPEC;
    float3 worldPos : WORLD_POS;
    float3 lightPos : LIGHT_POS;
    float3 camPos : CAM_POS;
    
};

// Note that if separate shader objects are not supported (this is only the case for old GLES3.0 devices), vertex
// shader output variable name must match exactly the name of the pixel shader input variable.
// If the variable has structure type (like in this example), the structure declarations must also be indentical.
void main(in  VSInput VSIn,
          out PSInput PSIn) 
{
    
    //PSIn.Pos = mul(float4(VSIn.Pos, 1.0), g_WorldViewProj);
    
    float4 pos = float4(VSIn.Pos,1.0);

    pos = mul(pos,g_World);
    
    //PSIn.Pos = mul(pos, g_Projection);

    PSIn.worldPos = pos.xyz;

    pos = mul(pos, g_View);

    PSIn.Pos = mul(pos, g_Projection);


//    pos = mul(pos,g_Projection);


  //  PSIn.Pos = pos;

    PSIn.Normal = normalize(mul(VSIn.Normal,g_World)).xyz;
    PSIn.Tangent = normalize(mul(VSIn.Tangent,g_World)).xyz;
    PSIn.lightPos = lightPos.xyz;
    PSIn.UV = VSIn.UV;
    PSIn.lightDiff = lightDiff.rgb;
    PSIn.lightSpec = lightSpec.rgb;
    PSIn.camPos = camPos.xyz;



    
}
