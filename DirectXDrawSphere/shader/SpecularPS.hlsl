// �ȼ� ���̴� �Է�.
struct ps_input
{
    float4 position : POSITION;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 worldPosition : TEXCOORD1;

    float3 cameraDirection : TEXCOORD2;
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
    float3 worldNormal = normalize(input.normal); // �����⸦ ��ġ�鼭 ���� �� �־ normalize �� ��.

    //// ����Ʈ ��ġ.
    //float3 lightPosition = float3(500.0f, 500.0f, -500.0f);

    // ����Ʈ ����.
    float3 lightDir = normalize(input.worldPosition - lightPosition);

    // ��ǻ�� ���� ����(���) power.
    float NdotL = saturate(dot(worldNormal, -lightDir));
    //NdotL = max(0, NdotL);
    //NdotL = saturate(NdotL);

    NdotL = pow((NdotL * 0.5f) + 0.5f, 2); // ���� ����Ʈ.

    float step = 3;
    NdotL = ceil(NdotL * step) / step; // �� ���̴� ��������.


    // ����ŧ��.
    float3 reflection = reflect(lightDir, worldNormal);
    float3 cameraDirection = normalize(input.cameraDirection);

    //// �� ���̴�. �ʹ� ���۵�����.
    //float specular = 0;
    //if (NdotL > 0)
    //{
    //    float RdotV = dot(reflection, -cameraDirection);
    //    specular = saturate(RdotV);
    //    specular = pow(specular, 15.0f);
    //}

    // ��-��(Blinn-Phong)
    float3 halfVector = normalize((-cameraDirection) + (-lightDir));
    float specular = 0;
    if (NdotL > 0)
    {
        float HdotN = saturate(dot(halfVector, worldNormal));
        specular = pow(HdotN, 100.0f);
    }

    float4 final = (NdotL * color) + (specular * color);

    return float4(specular, specular, specular, 1.0f);
}