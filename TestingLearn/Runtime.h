#pragma once

namespace pong
{
	/// <summary>
	/// Runtime behaviour.
	/// </summary>
	class Runtime
	{
	public:
		/// <summary>
		/// Running on the first frame.
		/// </summary>
		virtual void onAwake() = 0;

		/// <summary>
		/// Running every frame before a new frame drawn.
		/// </summary>
		virtual void onUpdate() = 0;

		/// <summary>
		/// Running on the last frame before termination.
		/// </summary>
		virtual void onEnd() = 0;
	};
}
