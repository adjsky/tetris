#pragma once
#include <array>

constexpr int GRIDWIDTH{ 10 };
constexpr int GRIDHEIGHT{ 20 };
constexpr float pieceSize{ 25.0f };
constexpr std::array<std::array<std::array<int, 2>, 3>, 7> points{
            {
                    {
                            {
                                    { 0, 1 },
                                    { 0, 1 },
                                    { 1, 1 }
                            }
                    },
                    {
                            {
                                    { 0, 1 },
                                    { 0, 1 },
                                    { 0, 1 }
                            }
                    },
                    {
                            {
                                    { 0, 1 },
                                    { 1, 1 },
                                    { 0, 1 }
                            }
                    },
                    {
                            {
                                    { 1, 1 },
                                    { 1, 1 },
                                    { 0, 0 }
                            }
                    },
                    {
                            {
                                    { 1, 0 },
                                    { 1, 0 },
                                    { 1, 1 }
                            }
                    },
                    {
                            {
                                    { 1, 0 },
                                    { 1, 1 },
                                    { 0, 1 }
                            }
                    },
                    {
                            {
                                    { 0, 1 },
                                    { 1, 1 },
                                    { 1, 0 }
                            }
                    }
            }
};
typedef std::array<std::array<int, GRIDWIDTH>, GRIDHEIGHT> mat_t;