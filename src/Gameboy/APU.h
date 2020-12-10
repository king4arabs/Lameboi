#pragma once

#include <queue>

#include "Memory.h"
#include "channel/SquareSweep.h"
#include "channel/Square.h"
#include "channel/Wave.h"
#include "Util/Common.h"
#include "Util/SDLHeaders.h"
#include "Util/Types.h"

class APU {
public:
	constexpr static int clock = 1048576;
	constexpr static int frequency = 44100;
	constexpr static int samples = 512;
	constexpr static float amplitude = 0.15f;

private:
	constexpr static int maxSampleCycles = (clock * 2) / frequency; //pushing samples every 2 T-Cycles
	constexpr static int maxSequencerCycles = clock / 512;

	u8 sequencer;
	u16 sequencerCycles;
	u8 sampleCycles;
	u16 bufferOffset;

	SDL_AudioDeviceID audio_device;
	std::array<float, samples * 2> sampleBuffer;

	friend SoundControl;
	SoundControl soundControl;

	SquareSweep squareSweep;
	Square square;
	Wave wave;

public:
	APU();
	~APU();

	void clean();

	//called in Scheduler::newMCycle
	void update();

	u8 read(u8 reg);
	void write(u8 reg, u8 value);
};