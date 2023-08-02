//***************************************************************************************
// color.fx by Frank Luna (C) 2011 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************


cbuffer cbPerObject
{
    float4x4 world;
    float4x4 worldViewProj;
    float4x4 invTworldViewProj;
};

cbuffer cbPerFrame
{
    float3 eyePosW;
    float4 meshColor;
    
    float3 lightDirection;
    
    float3 lightPosition;
    float4 lightColor;
};

struct VertexIn
{
    float3 PosL     : POSITION;
    float2 uv       : TEXCOORD;
    float3 Normal   : NORMAL;
};

struct VertexOut
{
    float4 PosH     : SV_POSITION;
    float3 PosW     : POSITION;
    float3 NormalW  : NORMAL;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
    
    vout.PosH       = mul(float4(vin.PosL, 1.0f), worldViewProj);
    vout.PosW       = mul(float4(vin.PosL, 1.f), world).xyz;
    vout.NormalW    = mul(vin.Normal, (float3x3)invTworldViewProj);

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    float3 N = normalize(pin.NormalW);
    float3 V = normalize(eyePosW - pin.PosW);
    float3 L = -normalize(pin.PosW - lightPosition);

    float4 Ambient  = float4(0.f, 0.f, 0.f, 0.f);
    float4 Diffuse  = float4(0.f, 0.f, 0.f, 0.f);
    float4 Specular = float4(0.f, 0.f, 0.f, 0.f);

    float AmbientStrength = 0.3f;
    Ambient = AmbientStrength * lightColor;
    
    float diffuseFactor = max(dot(N, L), 0.f);
    Diffuse = diffuseFactor * lightColor;
    
    float3 R = reflect(-L, N);
    float specularFactor = pow(max(dot(V, R), 0.f), 64);
    if (specularFactor > 0.f)
    {
        float SpecularStrength = 0.7f;
        Specular = specularFactor * SpecularStrength * lightColor;
    }

    return (Ambient + Diffuse + Specular) * meshColor;
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
