#ifndef SHADER_STATES_FX
#define SHADER_STATES_FX

// Particles
#define INACTIVE_EMITTER	-1
#define ACTIVE_EMITTER		0
#define CHILD				1

SamplerState SampLinearWrap
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

SamplerState SampLinearClamp
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

RasterizerState wireFrame
{
	FillMode = WIREFRAME;
	DepthBias = 800;
	AntialiasedLineEnable = true;
	CullMode = NONE;
};

RasterizerState noWireFrame
{
	FillMode = SOLID;
	CullMode = BACK;
	DepthBias = 0;
	MultiSampleEnable = true;
	AntialiasedLineEnable = false;
};

DepthStencilState DepthEnable
{
	DepthEnable = TRUE;
	DepthWriteMask = ALL;
	DepthFunc = LESS;
	StencilEnable = FALSE;
};

DepthStencilState DepthDisable
{
	DepthEnable = FALSE;
	DepthWriteMask = ZERO;
	DepthFunc = LESS;
	StencilEnable = FALSE;
};

BlendState BlendAlphaAdd
{
	BlendEnable[0] = TRUE;
	AlphaToCoverageEnable = FALSE;
	SrcBlend = SRC_ALPHA;
	DestBlend = INV_SRC_ALPHA;
	BlendOp = ADD;
	SrcBlendAlpha = ZERO;
	DestBlendAlpha = ZERO;
	BlendOpAlpha = ADD;
	RenderTargetWriteMask[0] = 0x0F;
};

BlendState AdditiveBlending
{
    AlphaToCoverageEnable = FALSE;
    BlendEnable[0] = TRUE;
    SrcBlend = SRC_ALPHA;
    DestBlend = ONE;
    BlendOp = ADD;
    SrcBlendAlpha = ZERO;
    DestBlendAlpha = ZERO;
    BlendOpAlpha = ADD;
    RenderTargetWriteMask[0] = 0x0F;
};

BlendState BlendDisable
{
	BlendEnable[0] = FALSE;
	AlphaToCoverageEnable = FALSE;
};

#endif