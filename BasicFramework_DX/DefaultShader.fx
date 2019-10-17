SamplerState SampleState : register(s0);

//Texture2D DefaultTex;


float2 PixelOffset;

cbuffer ConstantBuffer : register(b0)
{
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
};

struct VSInput
{
    float3 Position : POSITION;
    float2 UV : TEXCOORD0;

    float3 Normal : NORMAL;
    //float3 Tangent : TANGENT;
    //float3 Binormal : BINORMAL;
    float4 Color : COLOR;
};

struct PSInput
{
    float3 Position : SV_POSITION;
    float3 UV : TEXCOORD0;
    float3 Color : COLOR;
};

PSInput VS(VSInput Input)
{
    PSInput Output = (PSInput)0;

    Output.Position = mul(Input.Position, (float3x3) World);
    Output.Position = mul(Output.Position, (float3x3) View);
    Output.Position = mul(Output.Position, (float3x3) Projection);

    Output.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);

    return Output;
}

float4 PS(PSInput Input)
{
    return Input.Color;
}

technique11 GeometryTech
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
};