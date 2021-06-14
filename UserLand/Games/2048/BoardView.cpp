/*
 * Copyright (c) 2021, Krisna Pranav
 *
 * SPDX-License-Identifier: BSD-2-Clause
*/

// includes
#include "BoardView.h"
#include <LibGUI/Painter.h>
#include <LibGfx/Font.h>
#include <LibGfx/FontDatabase.h>
#include <LibGfx/Palette.h>

BoardView::BoardView(const Game::Board* board)
    : m_board(board)
{
}

BoardView::~BoardView()
{
}

void BoardView::set_board(const Game::Board* board)
{
    if (m_board == board)
        return;

    if (!board) {
        m_board = nullptr;
        return;
    }

    bool must_resize = !m_board || m_board->size() != board->size();

    m_board = board;

    if (must_resize)
        resize();

    update();
}

void BoardView::pick_font()
{
    String best_font_name;
    int best_font_size = -1;
    auto& font_database = Gfx::FontDatabase::the();
    font_database.for_each_font([&](const Gfx::Font& font) {
        if (font.family() != "Liza" || font.weight() != 700)
            return;
        auto size = font.glyph_height();
        if (size * 2 <= m_cell_size && size > best_font_size) {
            best_font_name = font.qualified_name();
            best_font_size = size;
        }
    });

    auto font = font_database.get_by_name(best_font_name);
    set_font(font);
}

size_t BoardView::rows() const
{
    if (!m_board)
        return 0;
    return m_board->size();
}

size_t BoardView::columns() const
{
    if (!m_board)
        return 0;
    if (m_board->is_empty())
        return 0;
    return (*m_board)[0].size();
}

void BoardView::resize_event(GUI::ResizeEvent&)
{
    resize();
}

void BoardView::resize()
{
    constexpr float padding_ratio = 7;
    m_padding = min(
        width() / (columns() * (padding_ratio + 1) + 1),
        height() / (rows() * (padding_ratio + 1) + 1));
    m_cell_size = m_padding * padding_ratio;

    pick_font();
}

void BoardView::keydown_event(GUI::KeyEvent& event)
{
    if (!on_move)
        return;

    switch (event.key()) {
    case KeyCode::Key_A:
    case KeyCode::Key_Left:
        on_move(Game::Direction::Left);
        break;
    case KeyCode::Key_D:
    case KeyCode::Key_Right:
        on_move(Game::Direction::Right);
        break;
    case KeyCode::Key_W:
    case KeyCode::Key_Up:
        on_move(Game::Direction::Up);
        break;
    case KeyCode::Key_S:
    case KeyCode::Key_Down:
        on_move(Game::Direction::Down);
        break;
    default:
        return;
    }
}
