#pragma once

namespace Qubit {
		template<typename dataX, typename dataY>
		struct pair {
			pair(dataX otherX, dataY otherY) : x(otherX), y(otherY) {}
			pair() = default;

			dataX x;
			dataY y;
		};
}