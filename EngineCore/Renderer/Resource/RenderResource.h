#pragma once

class RenderResource
{
public:
	virtual void CreateRHI() = 0;
	virtual void ReleaseRHI() = 0;
};