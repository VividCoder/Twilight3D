cbuffer Constants
{
    float4x4 g_WorldViewProj;
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
	float3 BiNormal : BINORMAL;
    
    
};

// Note that if separate shader objects are not supported (this is only the case for old GLES3.0 devices), vertex
// shader output variable name must match exactly the name of the pixel shader input variable.
// If the variable has structure type (like in this example), the structure declarations must also be indentical.
void main(in  VSInput VSIn,
          out PSInput PSIn) 
{
    PSIn.Pos   = mul( float4(VSIn.Pos,1.0), g_WorldViewProj);
	PSIn.Normal = VSIn.Normal;
	PSIn.BiNormal = VSIn.BiNormal;
	PSIn.Tangent = VSIn.Tangent;
    PSIn.UV = VSIn.UV;
}
