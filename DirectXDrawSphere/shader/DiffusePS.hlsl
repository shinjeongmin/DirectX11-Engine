// �ȼ� ���̴� �Է�.
struct ps_input
{
    float4 position : POSITION;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 worldPosition : TEXCOORD1;
};

// ����Ʈ ����.
cbuffer light : register(b0)
{
    float3 lightPosition;
    float pad1;
}

// �ؽ��� ������.
Texture2D image;
SamplerState samplerState;


// �ȼ� ���̴�.
//float4 main(float4 position : POSITION) : SV_TARGET
float4 main(ps_input input) : SV_TARGET
{
    // �̹����� ���� �����ϱ�.
    float4 color = image.Sample(samplerState, input.texCoord);

    // ��ǻ�� ���.
    float worldNormal = normalize(input.normal);

    //// ����Ʈ ��ġ.
    //float3 lightPosition = float3(500.0f, 500.0f, -500.0f);

    // ����Ʈ ����.
    float3 lightDir = normalize(input.worldPosition - lightPosition);

    // ��ǻ�� ���� ����(���) power.
    float NdotL = saturate(dot(worldNormal, -lightDir));
    //NdotL = max(0, NdotL);
    //NdotL = saturate(NdotL);

    // NdotL = pow((NdotL * 0.5f) + 0.5f, 2); // ���� ����Ʈ.

    float4 final = NdotL * color;

    return float4(NdotL, NdotL, NdotL, 1.0f);
    //return final;
}