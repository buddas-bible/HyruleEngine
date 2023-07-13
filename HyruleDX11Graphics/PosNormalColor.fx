//***************************************************************************************
// color.fx by Frank Luna (C) 2011 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************


cbuffer cbPerObject
{
    float4x4 worldViewProj;
    float4x4 invTworldViewProj;
};

cbuffer cbPerFrame
{
    float3 lightDirection;
    // float3 lightPosition;
    // float4 lightColor;
};

struct VertexIn
{
    float3 PosL     : POSITION;
    float2 uv       : TEXCOORD0;
    float3 Normal   : NORMAL;
};

struct VertexOut
{
    float4 PosH     : SV_POSITION;
    float Diffuse   : COLOR0;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
    float3 N = mul(vin.Normal, (float3x3)invTworldViewProj);
    N = normalize(N);
    float3 L = lightDirection;

    vout.PosH = mul(float4(vin.PosL, 1.0f), worldViewProj);
    vout.Diffuse = dot(N, L) * 0.5f + 0.5f;

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    float4 c = float4(1.f, 1.f, 1.f, 1.f);
    
    return c * pin.Diffuse;
}

technique11 Tech
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}