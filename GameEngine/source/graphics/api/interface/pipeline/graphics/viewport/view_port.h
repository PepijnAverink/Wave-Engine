#pragma once

namespace Graphics
{
	class ViewPort
	{
	public:
		ViewPort() = default;

		float X;
		float Y;
		float Width;
		float Height;
		float MinDepth;
		float MaxDepth;
	};
}