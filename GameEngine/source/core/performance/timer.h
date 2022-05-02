#pragma once


//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//******

//https://github.com/microsoft/DirectX-Graphics-Samples/blob/master/Samples/Desktop/D3D12Raytracing/src/D3D12RaytracingProceduralGeometry/util/StepTimer.h

class Timer
{

public:
	Timer()
	{
		QueryPerformanceFrequency(&m_QpcFrequency);
		QueryPerformanceCounter(&m_QpcLastTime);
		m_QpcMaxDelta = m_QpcFrequency.QuadPart / 10;
	}

	static const UINT64 m_sTicksPerSecond = 10000000;
	inline static double m_sTicksToSeconds(UINT64 ticks)
	{
		return static_cast<double>(ticks) / m_sTicksPerSecond;
	}

	inline static UINT64 m_sSecondsToTicks(double seconds)
	{
		return static_cast<UINT64>(seconds * m_sTicksPerSecond);
	}

	void ResetElapsedTime()
	{
		m_LeftOverTicks = 0;
		m_FramesPerSecond = 0;
		m_FramesThisSecond = 0;
		m_QpcSecondCounter = 0;
	}

	inline UINT64 GetElapsedTicks() const { return m_ElapsedTicks; }
	inline double GetElapsedSeconds() const { return m_sTicksToSeconds(m_ElapsedTicks); }
	inline UINT64 GetTotalTicks() const { return m_TotalTicks; }
	inline double GetTotalSeconds() const { return m_sTicksToSeconds(m_TotalTicks); }
	inline UINT32 GetFrameCount() const { return m_FrameCount; }
	inline UINT32 GetFramesPerSecond() const { return m_FrameCount; }
	inline void SetFixedTimeStep(bool isFixedTimeStep) { m_IsFixedTimeStep = isFixedTimeStep; }
	inline void SetTargetElapsedSeconds(double targetElapsed) { m_TargetElapsedTicks = m_sSecondsToTicks(targetElapsed); }


	typedef void(*LPUPDATEFUNC) (void);

	void Tick(LPUPDATEFUNC update = nullptr)
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);
		UINT64 timeDelta = currentTime.QuadPart - m_QpcLastTime.QuadPart;
		m_QpcLastTime = currentTime;
		m_QpcSecondCounter += timeDelta;


		// Clamp excessively larget time deltas
		if (timeDelta > m_QpcMaxDelta)
			timeDelta = m_QpcMaxDelta;

		// Convert QPC units into a canonical tick format. This cannot overflow due to the previous clamp.
		timeDelta *= m_sTicksPerSecond;
		timeDelta /= m_QpcFrequency.QuadPart;
		UINT32 lastFrameCount = m_FrameCount;

		if (m_IsFixedTimeStep)
		{
			// Fixed timestep update logic

			// If the app is running very close to the target elapsed time (within 1/4 of a millisecond) just clamp
			// the clock to exactly match the target value. This prevents tiny and irrelevant errors
			// from accumulating over time. Without this clamping, a game that requested a 60 fps
			// fixed update, running with vsync enabled on a 59.94 NTSC display, would eventually
			// accumulate enough tiny errors that it would drop a frame. It is better to just round 
			// small deviations down to zero to leave things running smoothly.

			if (abs(static_cast<int>(timeDelta - m_TargetElapsedTicks)) < m_sTicksPerSecond / 4000)
				timeDelta = m_TargetElapsedTicks;

			m_LeftOverTicks += timeDelta;

			while (m_LeftOverTicks >= m_TargetElapsedTicks)
			{
				m_ElapsedTicks = m_TargetElapsedTicks;
				m_TotalTicks += m_TargetElapsedTicks;
				m_LeftOverTicks -= m_TargetElapsedTicks;
				m_FrameCount++;
			}

			if (update)
				update();
		}
		else
		{
			// Variable timestep update logic.
			m_ElapsedTicks = timeDelta;
			m_TotalTicks += timeDelta;
			m_LeftOverTicks = 0;
			m_FrameCount++;
		}
	}
		
private:
	LARGE_INTEGER m_QpcFrequency;
	LARGE_INTEGER m_QpcLastTime;
	UINT64 m_QpcMaxDelta;

	UINT64 m_ElapsedTicks = 0;
	UINT64 m_TotalTicks = 0;
	UINT64 m_LeftOverTicks = 0;

	UINT32 m_FrameCount = 0;
	UINT32 m_FramesPerSecond = 0;
	UINT32 m_FramesThisSecond = 0;
	UINT64 m_QpcSecondCounter = 0;

	bool m_IsFixedTimeStep;
	UINT64 m_TargetElapsedTicks = m_sTicksPerSecond / 60;
};
