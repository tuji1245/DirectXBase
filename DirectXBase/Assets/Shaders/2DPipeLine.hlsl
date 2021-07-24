struct VS_INPUT
{
	float3 Pos : POSITION;
	float4 Col : TEXCOORD;
};
struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float4 Col : TEXCOORD;
};

PS_INPUT vsMain(VS_INPUT pos)
{
	PS_INPUT o = (PS_INPUT)0;
	o.Pos = float4(pos.Pos, 1);
	o.Col = pos.Col;
	return o;
}

float4 psMain(PS_INPUT input) : SV_TARGET
{
	return input.Col;
}