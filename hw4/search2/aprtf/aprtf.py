#!/usr/bin/env python3

# APRTF -- an automated test framework for PageRank
# version 1.3

import os
import random
import collections
import shutil
import re
import subprocess
import copy
import sys

# ------- configuration section
search_executable = os.path.join('..', 'search-shell')
webpage_file_dir = "generated_webpages"
run_file_dir = "generated_run_files" # directory to put files used for running the program
delete_webpages = True # if true, webpages will be deleted after a run where all tests pass
use_valgrind = False # if true, valgrind will be used to run test cases
fast_fail = True # if true, abort the program after one test fails

compare_tolerance = .0001 # tolerance below which pages will be considered to have the same page rank

# file paths for generated files
index_file_path = os.path.join(run_file_dir, "index.txt")
query_file_path = os.path.join(run_file_dir, "query.txt")
output_file_path = os.path.join(run_file_dir, "output.txt")

# command to run test cases with valgrind
valgrind_command = ['valgrind', '--tool=memcheck', '--leak-check=yes']

# read lorem ipsum text into an array
print("Parsing lorem ipsum file...")
lorem_ipsum_file = open("lorem-ipsum-bank.txt", "r")
lorem_ipsum_array = lorem_ipsum_file.read().split(" ")
for index in range(0, len(lorem_ipsum_array)):
	lorem_ipsum_array[index] = lorem_ipsum_array[index].strip().lower()

# from https://stackoverflow.com/questions/1276764/stripping-everything-but-alphanumeric-chars-from-a-string-in-python
alphanumeric_regex = re.compile('[\W_]+')

# function to get random sequences from that array
def generate_random_lorem_ipsum(num_words):
	
	word_list = []

	for counter in range(0, num_words):
		index = random.randrange(0, len(lorem_ipsum_array))
		sanitized_word = alphanumeric_regex.sub('', lorem_ipsum_array[index]) # remove all non-alphanumeric characters, for simplicity
		word_list.append(sanitized_word)

	return word_list
	

# inserts a value into a map of sets.
# Creates the map key if it does not yet exist.
def insert_into_set_map(set_map, key, value):
	if key in set_map:
		set_map[key].update([value])
	else:
		set_map[key] = set([value])

# generates the given number of word files with the given parameters, from random lorem ipsum text
def generate_word_files(test_data, words_per_file, link_probablility, num_files):
	
	test_data.files = set()
	test_data.words = {}
	test_data.links_by_source = {}
	test_data.links_by_dest = {}
	test_data.pages_by_word = {}

	# generate random filenames
	file_names = []
	for index in range(num_files):

		# generate a unique file name
		file_basename = generate_random_lorem_ipsum(1)[0]
		file_name = os.path.join(webpage_file_dir, file_basename + '.md')
		number_suffix = 1

		while file_name in file_names:
			file_name = os.path.join(webpage_file_dir, file_basename + str(number_suffix) + '.md')
			number_suffix = number_suffix + 1

		file_names.append(file_name)

	# create each file and fill it with content
	for index in range(num_files):

		num_words = random.randrange(words_per_file[0], words_per_file[1]+1)
		file_words_list = generate_random_lorem_ipsum(num_words)

		file_pointer = open(file_names[index], "w")
		file_string = ""

		current_line_length = 0;

		files_to_avoid_linking_to = set([file_names[index]])

		# write words to file, replacing some of them with links
		for wordIndex in range(0, len(file_words_list)):

			random_word = generate_random_lorem_ipsum(1)[0] # word to insert

			# record word in words to pages map
			insert_into_set_map(test_data.pages_by_word, random_word, file_names[index])

			text_to_write = ""

			generated_link = False
			# possibly print link to random other file
			if random.random() < link_probablility:

				other_file = random.choice(file_names) # file path to link to

				if other_file not in files_to_avoid_linking_to:

					generated_link = True
					text_to_write = "[" + random_word + "](" + other_file + ")"

					# add link to data
					insert_into_set_map(test_data.links_by_source, file_names[index], other_file)
					insert_into_set_map(test_data.links_by_dest, other_file, file_names[index])

					# make sure to avoid generating a repeated link to this same file
					files_to_avoid_linking_to.update([other_file])

			if not generated_link:
				text_to_write = random_word

			# try to keep lines under 80 characters
			if len(text_to_write) + 1 + current_line_length > 80:
				text_to_write = "\n" + text_to_write
				current_line_length = len(text_to_write)
			else:
				if current_line_length > 0:
					text_to_write = " " + text_to_write
				
				current_line_length += len(text_to_write)

			file_pointer.write(text_to_write)
			file_string += text_to_write

			# insert data into test data struct
			test_data.files.update([file_names[index]])
			test_data.words[file_names[index]] = file_words_list

		file_pointer.close()


# returns a list containing a random query of a random number of words
def gen_random_query():
	
	max_num_words = 4
	num_words = random.randrange(1, max_num_words + 1)
	words_to_search = generate_random_lorem_ipsum(num_words)

	# build query, appending "AND" or "OR" at the start
	query_words_list = [random.choice(('PROR', 'PRAND'))] + ['r'] + words_to_search
	
	return query_words_list

# search the search data for pages containing the given word, and return a set of results.
# Returns an empty set if there are no results
def search_for_word(test_data, word):
	if word in test_data.pages_by_word:
		return set(test_data.pages_by_word[word])
	else:
		return set()

# runs the given query and determines which pages would result from it.
# Supports OR and AND queries.
# Assumes that the query is well-formed, and was generated by gen_random_query()
def predict_query_results(test_data, query):
	if query[0] == 'PRAND':
		
		# run first query
		aggregate = search_for_word(test_data, query[2])

		# run subsequent queries
		if len(query) > 3:
			for word in query[3:]:
				pages_with_word = search_for_word(test_data, word)
				aggregate &= pages_with_word # from https://www.saltycrane.com/blog/2008/01/how-to-find-intersection-and-union-of/

		return aggregate

	else: # "PROR" query
		aggregate = set()
		# run subsequent queries
		for word in query[2:]:
			pages_with_word = search_for_word(test_data, word)
			aggregate |= pages_with_word

		return aggregate

# Given a set of pages, returns an expanded set of pages that link to or are linked to by those pages
def get_expanded_results(test_data, results):
	
	extra_results = set()

	for page in results:

		if page in test_data.links_by_source:
			extra_results.update(test_data.links_by_source[page])

		if page in test_data.links_by_dest:
			#print("links by dest for %s: %s", (page, " ".join(test_data.links_by_dest[page])))
			extra_results.update(test_data.links_by_dest[page])

	return extra_results | results

# Writes crawler files for all tests in this run
def generate_config_files(test_data):

	# write index file
	index_file = open(index_file_path, "w")
	for file in test_data.files:
		index_file.write(file + '\n')
	index_file.close()


# runs the user's search program on the given query file, and returns a tuple of the reported number of pages from the output file, 
# and the list of the result webpages in order and their ranks, or -1 and an error message if it failed
def run_user_search_program(command_line, query_file):

	output_file = open(output_file_path, "w+")
	return_code = subprocess.call(command_line, stdin=query_file, stdout=output_file)

	print("Executing: " + " ".join(command_line) + " < " + query_file_path + " > " + output_file_path)

	output_file.seek(0)

	if return_code == 0:

		# read user program output from file
		file_lines = output_file.readlines()

		if len(file_lines) < 1:
			return (-1, "Output file was empty!")

		num_pages = -1
		pages = []
		ranks = {}
		in_results = False

		for line in file_lines:

			if len(line.strip()) <= 0:
				# blank line
				pass
			elif line[0] == '$':
				if not in_results:
					# start of results is on next line
					in_results = True
				else:
					# hit end of results
					break

			elif in_results and num_pages == -1 and line.strip().isdigit():
				# found page number
				try:
					num_pages = int(line)
				except ValueError:
					return (-1, "Number format error in result count") 

			elif in_results: 

				if not ":" in line:
					return (-1, "Format error in output line: \"" + line[0:-1] + "\"") 

				# found an output line
				page,rank = line.split(":")
				page = page.strip()

				try:
					rank = float(rank.strip())
				except ValueError:
					return (-1, "Number format error in output line: \"" + line[0:-1] + "\"") 

				pages.append(page)
				ranks[page] = rank;
			
		output_file.close()
		return (num_pages, pages, ranks)

	else:
		output_file.close()
		return (-1, "User search program crashed (returned nonzero exit code %d)" % (return_code,))

# returns a dict of each page in page list to its rank
def rank_pages(test_data, page_list, pr_restart_probability, pr_step_number):

	# files to remove from link sets
	excluded_files = test_data.files - page_list

	# make copies of link data, and add self loops for all pages
	incoming_links = copy.deepcopy(test_data.links_by_dest)
	outgoing_links = copy.deepcopy(test_data.links_by_source)

	for page in test_data.files:
		insert_into_set_map(incoming_links, page, page)
		incoming_links[page] -= excluded_files

		insert_into_set_map(outgoing_links, page, page)
		outgoing_links[page] -= excluded_files

		#print("outgoing_links for %s: %s" % (page, outgoing_links[page]))

	num_results = len(page_list)

	# start with the random surfer being at any node with equal probability
	node_probabilities_prev_iter = dict((page, 1/float(num_results)) for page in page_list)
	
	for counter in range(0, pr_step_number):
		node_probabilities_curr_iter = {}

		for curr_page in page_list:

			incoming_link_probability = 0

			for page_with_link in incoming_links[curr_page]:
				#print("run %d: outgoing_links[%s]: %d" % (counter, page_with_link, len(outgoing_links[page_with_link])))

				# add the liklihood that a user was on page_with_link and traveled to this page
				incoming_link_probability += node_probabilities_prev_iter[page_with_link] * (1 / float(len(outgoing_links[page_with_link])))

			node_probabilities_curr_iter[curr_page] = (1 - pr_restart_probability) * incoming_link_probability + (pr_restart_probability / float(num_results))

			#print("run %d: current rank[%s] = %.04f" % (counter, curr_page, node_probabilities_curr_iter[curr_page]))

		# prepare for next cycle
		node_probabilities_prev_iter = node_probabilities_curr_iter

	# done!
	return node_probabilities_curr_iter

# returns true iff the results are in the right order according to the page rank
def check_user_pagerank(user_pages, user_ranks, page_ranks):

	pr_of_last_result = float('inf')
	for page in user_pages:
		#print("pr_of_last_result: %.04f, page_ranks[page]: %.04f" % (pr_of_last_result, page_ranks[page]))
		if page_ranks[page] > pr_of_last_result + compare_tolerance:
			return False

		if abs(user_ranks[page] - page_ranks[page]) > compare_tolerance:
			return False

		pr_of_last_result = page_ranks[page]

	return True

# random_seed - random seed to use
# words_per_file - amount of words to generate in each file, tuple of lower and upper bounds
# link_probablility - double probability that a word in each file will be a link to a random other file
# num_files - number of files to generate and test on
# num_queries - number of random queries to run
def test_page_rank(random_seed, words_per_file, link_probablility, num_files, num_queries):

	# values hardcoded  for sp2020 assignment
	pr_restart_probability = .15
	pr_step_number = 20

	# set random seed
	random.seed(random_seed)

	# create test data structure 
	test_data = collections.namedtuple('TestData', ['files', 'words', 'links_by_source', 'links_by_dest', 'pages_by_word'])

	# remove all previous generated files
	shutil.rmtree(webpage_file_dir, True)
	shutil.rmtree(run_file_dir, True)
	os.mkdir(webpage_file_dir)
	os.mkdir(run_file_dir)

	if not os.path.exists(search_executable):
		print("Error: search executable \"%s\" does not exist!" % search_executable)
		return

	print("Generating %d word files..." % num_files)	
	generate_word_files(test_data, words_per_file, link_probablility, num_files)

	print("Generating config files...")	
	generate_config_files(test_data)
	#print(test_data.pages_by_word)
	#print(test_data.links_by_source)
	#print(test_data.links_by_dest)

	for counter in range(0, num_queries):

		# if false, a failure message will be printed out at the end
		successful = True

		page_ranks = None
		failure_message = ""
		if os.path.exists(output_file_path):
			os.remove(output_file_path)

		query = gen_random_query()

		print("----------------- Running random query %d: \"%s\"" % (counter + 1, " ".join(query)))

		base_results = predict_query_results(test_data, query)
		expanded_results = get_expanded_results(test_data, base_results)

		# generate query file
		query_file = open(os.path.join(run_file_dir, "query.txt"), "w+")
		query_file.write(" ".join(query) + "\n")
		query_file.write("QUIT\n\n")
		query_file.seek(0)

		# run user program
		user_prog_cmdline = [search_executable, index_file_path]
		if use_valgrind:
			user_prog_cmdline = valgrind_command + user_prog_cmdline
			
		run_result = run_user_search_program(user_prog_cmdline, query_file)
		run_succeeded= run_result[0] >= 0
			
		if run_succeeded:
			num_pages, user_pages, user_ranks = run_result
			user_pages_set = set(user_pages)
		else:
			failure_message = run_result[1]
			successful = False

		query_file.close()

		if successful:

			if num_pages != len(user_pages):
				failure_message = "User search program said it returned %d results, but actually produced %d webpages!" % (num_pages, len(user_pages))
				successful = False

			if len(expanded_results) != num_pages:
				failure_message = "User search program returned wrong number of results!  Expected %d, got %d!" % (len(expanded_results), num_pages)
				successful = False

		# now compare content of results (unordered)
		if successful:
			if set(user_pages) != expanded_results:
				failure_message = "User search program returned wrong set of results:"
				print("-" + "\n-".join(set(user_pages)))
				successful = False

		# now calculate page rank
		if successful:
			page_ranks = rank_pages(test_data, expanded_results, pr_restart_probability, pr_step_number)
			successful = check_user_pagerank(user_pages, user_ranks, page_ranks)
			if not successful:
				failure_message = "Pages are ranked incorrectly!"
			
		if successful:
			print("----------------- \x1b[92mPassed! Correctly produced %d results!\x1b[39m" % num_pages)
		else:
			print("----------------- \x1b[91mFailed! %s\x1b[39m" % failure_message)
			print(">> Index file was: %s" % index_file_path)
			print(">> Query file was: %s" % query_file_path)
			print(">> Output file was: %s" % output_file_path)
			print("")

			if len(expanded_results) == 0:
				print(">> Should have returned no results!")
			elif run_succeeded:

				if page_ranks is None:
					print(">> Should have returned the following pages: \n-" + "\n-".join(expanded_results))

					print(">> Pages that match query: \n-" + "\n-".join(base_results))
					print(">> Pages that should have been found through result set expansion: \n-" + "\n-".join(expanded_results - base_results))

					extra_pages = user_pages_set - expanded_results
					if len(extra_pages) > 0:
						print(">> Pages present in user results that should not have been: \n-" + "\n-".join(extra_pages))

					missing_pages = expanded_results - user_pages_set
					if len(extra_pages) > 0:
						print(">> Pages missing in user results: \n-" + "\n-".join(missing_pages))
				else:
					print(">> Correct page ranks:")
					for page, rank in sorted(page_ranks.items(), reverse=True, key=lambda kv: (kv[1],kv[0])):
						print("-%s: %s" % (page, rank))

					rank_sum = 0
					for rank in user_ranks.values():
						rank_sum += rank

					if abs(rank_sum - 1.0) > compare_tolerance:
						print(">> Incorrect rank sum detected")
						print("Your pageranks must sum ou to roughly 1, but instead they sum up to %.04f" % rank_sum)
					else:
						print(">> Your ranks do sum to roughly 1, so your basic math seems to be OK")

			# break out of tests so user can debug
			if fast_fail:
				sys.exit(1)

	print("All test cases passed!")
	return True


if __name__ == '__main__':
	test_page_rank(4, (50, 100), .05, 20, 10)
	test_page_rank(129, (50, 100), .05, 20, 10)
	test_page_rank(-50, (100, 200), .007, 50, 200)
	test_page_rank(-50001, (30, 50), .01, 1000, 2)