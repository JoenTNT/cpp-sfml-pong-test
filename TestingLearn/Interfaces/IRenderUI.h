#pragma once

namespace pong
{
	class IRenderUI
	{
	public:
		/// <summary>
		/// Renders User interface. Run this in update.
		/// </summary>
		virtual void render() = 0;
	};
}