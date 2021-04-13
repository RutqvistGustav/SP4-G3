#pragma once

enum class RenderSamplerFilter
{
	Point,
	Bilinear,
};

struct BaseRenderData
{
	RenderSamplerFilter mySamplerFilter{ RenderSamplerFilter::Point };
};
