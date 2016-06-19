/*
 *   Copyright 2016 Robert C. Taylor
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


/**
 * @file source.h
 *
 * Convenience header that includes all signal source-related headers.
 *
 * @package Quasar
 * @version 4.0.0-beta
 * @author Zbigniew Siciarz, Robert C. Taylor
 * @date 2007-2014
 * @since 3.0.0
 */


#ifndef QUASAR_SOURCE_H
#define QUASAR_SOURCE_H

#include "source/SignalSource.h"
#include "source/Frame.h"
#include "source/FramesCollection.h"
#include "source/PlainTextFile.h"
#include "source/RawPcmFile.h"
#include "source/generator/Generator.h"
#include "source/generator/SineGenerator.h"
#include "source/generator/SquareGenerator.h"
#include "source/generator/TriangleGenerator.h"
#include "source/generator/PinkNoiseGenerator.h"
#include "source/generator/WhiteNoiseGenerator.h"
#include "source/generator/ChirpGenerator.h"
#include "source/window/BarlettWindow.h"
#include "source/window/BlackmanWindow.h"
#include "source/window/FlattopWindow.h"
#include "source/window/GaussianWindow.h"
#include "source/window/HammingWindow.h"
#include "source/window/HannWindow.h"
#include "source/window/RectangularWindow.h"
#include "source/window/WelchWindow.h"
#include "source/window/BlackmanHarrisWindow.h"
#include "source/window/NuttallWindow.h"
#include "source/window/BlackmanNuttallWindow.h"
#include "source/window/CosineWindow.h"
#include "source/filter/RaisedCosineFilter.h"
#include "source/filter/SincFilter.h"

#endif // QUASAR_SOURCE_H
