DIMACS10_DIR= datasets/dimacs10
DIMACS10_ARCHIVE= datasets/dimacs10/archive

DIMACS10_BIN = $(DIMACS10_DIR)/make_edge_list

DIMACS10 = \
	ori/kron_g500-simple-logn16.edgelist.txt.bz2 \
	ori/kron_g500-simple-logn17.edgelist.txt.bz2 \
	ori/kron_g500-simple-logn18.edgelist.txt.bz2 \
	ori/citationCiteseer.edgelist.txt.bz2 \
	ori/coAuthorsCiteseer.edgelist.txt.bz2 \
	ori/coAuthorsDBLP.edgelist.txt.bz2 \
	ori/coPapersCiteseer.edgelist.txt.bz2 \
	ori/coPapersDBLP.edgelist.txt.bz2

DIMACS10_LARGE = \
	ori/kron_g500-simple-logn19.edgelist.txt.bz2 \
	ori/kron_g500-simple-logn20.edgelist.txt.bz2 \
	ori/kron_g500-simple-logn21.edgelist.txt.bz2


$(DIMACS10): $(DIMACS10_BIN)

$(DIMACS10_LARGE): $(DIMACS10_BIN)

$(DIMACS10_BIN): $(DIMACS10_BIN).cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

ori/%.edgelist.txt.bz2: $(DIMACS10_ARCHIVE)/%.graph.bz2
	mkdir -p ori
	bzip2 -dc $< | $(DIMACS10_BIN) | bzip2 > $@

.SECONDARY:

$(DIMACS10_ARCHIVE)/kron_%.graph.bz2:
	mkdir -p $(DIMACS10_ARCHIVE)
	cd $(DIMACS10_ARCHIVE) ; $(WGET) http://www.cc.gatech.edu/dimacs10/archive/data/kronecker/$(notdir $@)

$(DIMACS10_ARCHIVE)/c%.graph.bz2:
	mkdir -p $(DIMACS10_ARCHIVE)
	cd $(DIMACS10_ARCHIVE) ; $(WGET) http://www.cc.gatech.edu/dimacs10/archive/data/coauthor/$(notdir $@)

