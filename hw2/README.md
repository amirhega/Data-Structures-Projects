My gitint creates a simulation of git that has features like add, commit, diff, tag, checkout, create, edit and more. My implementation uses mostly maps, one set, and one vector that stores the data when the user creates data within the restraints. My maps rely heavily on the CommitObj struct as these have valuable data like diffs_, parent_ and commit name in which I center most of my work around these values. 

Makefile needs to be cleaned after every make to make again.

My hw2 runtime analysis section is in a new file hw2.pdf.