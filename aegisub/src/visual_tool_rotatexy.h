// Copyright (c) 2011, Thomas Goyne <plorkyeran@aegisub.org>
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//
// Aegisub Project http://www.aegisub.org/

/// @file visual_tool_rotatexy.h
/// @see visual_tool_rotatexy.cpp
/// @ingroup visual_ts
///

#include "visual_feature.h"
#include "visual_tool.h"

class VisualToolRotateXY : public VisualTool<VisualDraggableFeature> {
	float angle_x; /// Current x rotation
	float angle_y; /// Current y rotation
	float angle_z; /// Current z rotation

	float orig_x; ///< x rotation at the beginning of the current hold
	float orig_y; ///< y rotation at the beginning of the current hold

	Feature *org;

	void DoRefresh();
	void Draw();
	void UpdateDrag(Feature *feature);
	bool InitializeHold();
	void UpdateHold();
public:
	VisualToolRotateXY(VideoDisplay *parent, agi::Context *context);
};
