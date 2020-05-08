cbuffer Constants
{
    float4x4 g_View;
    float4x4 g_Model;
    float4x4 g_Projection;
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
    float3 eyeDir : E_DIR;
    float3 lightDir : LIGHT_DIR;
    float3 lightDiff : LIGHT_DIFF;
    float3 lightSpec : LIGHT_SPEC;

    
};

// Note that if separate shader objects are not supported (this is only the case for old GLES3.0 devices), vertex
// shader output variable name must match exactly the name of the pixel shader input variable.
// If the variable has structure type (like in this example), the structure declarations must also be indentical.
void main(in  VSInput VSIn,
          out PSInput PSIn) 
{
    
    //PSIn.Pos = mul(float4(VSIn.Pos, 1.0), g_WorldViewProj);
    
    float4 pos = float4(VSIn.Pos, 1.0);
    
    pos = mul(pos, g_Model);
    pos = mul(pos, g_View);
    pos = mul(pos, g_Projection);
    
    PSIn.Pos = pos;
    
    PSIn.UV = VSIn.UV;
    
    PSIn.Normal = normalize(mul(VSIn.Normal, (float3x3) g_Model));
    
    float3 worldPos = mul(VSIn.Pos.xyz, (float3x3) g_Model);
    
    PSIn.lightDir = normalize(lightPos.xyz - worldPos);
    PSIn.eyeDir = normalize(camPos.xyz - worldPos);
    PSIn.Tangent = normalize(mul(VSIn.Tangent, (float3x3) g_Model));
    PSIn.lightDiff = lightDiff.rgb;
    PSIn.lightSpec = lightSpec.rgb;
    
}
