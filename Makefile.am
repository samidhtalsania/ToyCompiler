AUTOMAKE_OPTIONS = foreign

install-exec-local:
	lemon PrevotyParserGrammar.y &&
	mv PrevotyParserGrammar.c PrevotyParserGrammar.cpp &&
	re2c PrevotyLexer.re > PrevotyLexer.cpp


INCLUDE = $(PROJECT_ROOT)/includes

AM_CPPFLAGS = -I $(INCLUDE)
AM_CFLAGS = -I $(INCLUDE)
AM_CXXFLAGS = -I $(INCLUDE)
bin_PROGRAMS = prevoty

prevoty_SOURCES = \
			main.cpp \
			Token.cpp \
			syntax_exception.cpp \
			ParserWrapper.cpp \
			ParserFactory.cpp \
			PrevotyParserGrammar.cpp \
			PrevotyLexer.cpp \
			LexerFactory.cpp