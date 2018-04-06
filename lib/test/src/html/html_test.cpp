/*
 markdown_benchmark.cpp     MindForger markdown test

 Copyright (C) 2016-2018 Martin Dvorak <martin.dvorak@mindforger.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdlib>
#include <iostream>
#include <memory>
#include <cstdio>
#include <unistd.h>

#include <gtest/gtest.h>

#include "../../src/representations/html/html_outline_representation.h"
#include "../../src/mind/mind.h"
#include "../../src/persistence/filesystem_persistence.h"

using namespace std;

extern char* getMindforgerGitHomePath();

TEST(HtmlTestCase, Outline)
{    
    string fileName{"/lib/test/resources/benchmark-repository/memory/meta.md"};
    fileName.insert(0, getMindforgerGitHomePath());

    m8r::Configuration& config = m8r::Configuration::getInstance();
    config.clear();
    config.setConfigFilePath("/tmp/cfg-htc-o.md");
    config.setActiveRepository(config.addRepository(m8r::RepositoryIndexer::getRepositoryForPath(fileName)));
    m8r::Mind mind(config);
    m8r::HtmlOutlineRepresentation htmlRepresentation{mind.remind().getOntology()};
    m8r::MarkdownOutlineRepresentation markdownRepresentation(mind.remind().getOntology());
    mind.think();

    ASSERT_GE(mind.remind().getOutlinesCount(), 1);

    // MD: 1.1MiB
    string markdown{};
    markdownRepresentation.to(mind.remind().getOutlines()[0], &markdown);
    cout << "Markdown " << markdown.size() << "B" << endl;

    string html{};
    htmlRepresentation.to(&markdown, &html);

    cout << "= BEGIN HTML =" << endl << html << endl << "= END HTML =" << endl;
}

TEST(HtmlTestCase, Note)
{
    string fileName{"/lib/test/resources/benchmark-repository/memory/meta.md"};
    fileName.insert(0, getMindforgerGitHomePath());

    m8r::Configuration& config = m8r::Configuration::getInstance();
    config.clear();
    config.setConfigFilePath("/tmp/cfg-htc-n.md");
    config.setActiveRepository(config.addRepository(m8r::RepositoryIndexer::getRepositoryForPath(fileName)));
    m8r::Mind mind(config);
    m8r::HtmlOutlineRepresentation htmlRepresentation{mind.remind().getOntology()};
    m8r::MarkdownOutlineRepresentation markdownRepresentation(mind.remind().getOntology());
    mind.think();

    ASSERT_GE(mind.remind().getOutlinesCount(), 1);

    string html{};
    htmlRepresentation.to(mind.remind().getOutlines()[0]->getNotes()[0], &html);

    cout << "= BEGIN HTML =" << endl << html << endl << "= END HTML =" << endl;
}

TEST(HtmlTestCase, NoteLinks)
{
    string fileName{"/lib/test/resources/markdown-repository/memory/feature-html-links.md"};
    fileName.insert(0, getMindforgerGitHomePath());

    m8r::Configuration& config = m8r::Configuration::getInstance();
    config.clear();
    config.setConfigFilePath("/tmp/cfg-antc-nl.md");
    config.setActiveRepository(config.addRepository(m8r::RepositoryIndexer::getRepositoryForPath(fileName)));
    m8r::Mind mind(config);
    m8r::HtmlOutlineRepresentation htmlRepresentation{mind.remind().getOntology()};
    mind.think();

    ASSERT_GE(mind.remind().getOutlinesCount(), 1);

    string html{};
    htmlRepresentation.to(mind.remind().getOutlines()[0]->getNotes()[0], &html);

    // links are NOT resolved - they are kept as they are
    cout << "= BEGIN HTML =" << endl << html << endl << "= END HTML =" << endl;
}
