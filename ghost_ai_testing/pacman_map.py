import numpy
import os 
import random
import time

class pacman_map:

	def __init__(self, custom_map=None):
		if custom_map:
			with open(custom_map, "rb") as f:
				self._map = numpy.array([list(line) for line in f.read().strip().split()]).astype(int)
		else:
			self._map = self._create_default_map()
		self._init_pacman()
		self._init_ghost()

	def __str__(self):
		return str(self._map)

	def _create_default_map(self):
		return numpy.array([
		[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
		[0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0],
		[0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0],
		[0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0],
		[0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0],
		[0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0],
		[0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0],
		[0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0],
		[0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 2, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0],
		[1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1],
		[0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0],
		[0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0],
		[0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0],
		[0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0],
		[0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0],
		[0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0],
		[0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0],
		[0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0],
		[0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0],
		[0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0],
		[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
		])

	def _init_pacman(self):
		x = random.choice(range(self._map.shape[0]))
		y = random.choice(range(self._map.shape[1]))
		if self._map[x, y] != 1:
			return self._init_pacman()
		print("initializing pacman at {}, {}".format(x, y))
		self._map[x, y] = 3

	def _init_ghost(self):
		y = random.choice(range(self._map.shape[0]))
		x = random.choice(range(self._map.shape[1]))
		if self._map[x, y] != 1:
			return self._init_ghost()
		print("initializing ghost at {}, {}".format(x, y))
		self._map[x, y] = 4

	def map(self):
		return self._map


class pathfinder:

	def __init__(self, pacman_map, heuristic="manhattan"):
		self._map = pacman_map.map()
		self.open_tiles = []
		self.closed_tiles = []
		self.backtrack = {}
		self.path = []
		assert heuristic in ["manhattan", "euclidean"], "{} not a know heuristic".format(heuristic)
		self.heuristic = heuristic

	def _find_pacman(self):
		return tile(tuple([int(pos) for pos in numpy.where(self._map == 3)]))

	def _find_ghost(self):
		pos = tuple([int(pos) for pos in numpy.where(self._map == 4)])
		h_score = self._calculate_h_score(pos, self._find_pacman())
		self.backtrack[pos] = None
		return tile(pos, 0, h_score, h_score)

	def _search_adjacent_tiles(self, t):
		pos = t.pos
		up = tuple([pos[0], pos[1] - 1]) if (pos[1] - 1) >= 0 else None
		right = tuple([pos[0] + 1, pos[1]]) if (pos[0] + 1) >= 0 else None
		down =  tuple([pos[0], pos[1] + 1]) if (pos[1] + 1) < self._map.shape[0] else None
		left = tuple([pos[0] - 1, pos[1]]) if (pos[0] - 1) < self._map.shape[1] else None
		adjacent_tiles = [tile(p) for p in [up, right, down, left] if (self._map[p] == 1 or self._map[p] == 3)  and tile(p) not in self.closed_tiles]
		return adjacent_tiles
		
	def _calculate_h_score(self, base_pos, target_pos):
		if self.heuristic == "manhattan":
			return abs(base_pos[0] - target_pos[0]) + abs(base_pos[1] - target_pos[1])
		elif self.heuristic == "euclidean":
			return pow(abs(base_pos[0] - target_pos[0]),2) + pow(abs(base_pos[1] - target_pos[1]),2)

	def _a_star(self, base_tile, target_tile):
		self.closed_tiles.append(base_tile)
		adjacent_tiles = self._search_adjacent_tiles(base_tile)
		for t in adjacent_tiles:
			t.g_score = base_tile.g_score + 1
			t.h_score = self._calculate_h_score(t, target_tile)
			t.f_score = t.g_score + t.h_score

		min_f_value_adjacent = min(adjacent_tiles) if adjacent_tiles else None
		min_f_value_open = min(self.open_tiles) if self.open_tiles else None
		if min_f_value_open and min_f_value_adjacent:
			min_f_value = min_f_value_adjacent if min_f_value_adjacent <= min_f_value_open else min_f_value_open
		else:
			min_f_value = min_f_value_adjacent or min_f_value_open
		for t in adjacent_tiles:
			if t not in self.open_tiles:
				self.backtrack[t.pos] = base_tile.pos
				self.open_tiles.append(t)
		self.open_tiles.remove(min_f_value)
		if min_f_value == target_tile:
			return self._backtrack()
		self._a_star(min_f_value, target_tile)

	def _backtrack(self):
		current_path = self._find_pacman().pos
		start = self._find_ghost().pos
		while current_path != start:
			current_path = self.backtrack[current_path]
			if current_path != start:
				self.path.append(current_path)
		self.path.reverse()

	def _draw_map(self):
		for _ in range(3):
			tmp = numpy.copy(self._map)
			for t in self.closed_tiles:
				print(chr(27) + "[2J")
				tmp[t.pos] = 7
				print tmp
				print "searching"
				print "heuristic = {}, iterations = {}, path length = {}".format(self.heuristic, len(self.closed_tiles), len(self.path))
				time.sleep(0.05)
			for pos in self.path:
				print(chr(27) + "[2J")
				tmp[pos] = 8
				print tmp
				print "backtracking"
				print "heuristic = {}, iterations = {}, path length = {}".format(self.heuristic, len(self.closed_tiles), len(self.path))
				time.sleep(0.05)
			time.sleep(0.05)

	def find(self):
		self._a_star(self._find_ghost(), self._find_pacman())
		self._draw_map()



class tile:

	def __init__(self, pos, g_score=None, h_score=None, f_score=None):
		self.pos = pos
		self.g_score = g_score
		self.h_score = h_score
		self.f_score = f_score

	def __eq__(self, other):
		return self.pos == other.pos

	def __neq__(self, other):
		return self.pos != other.pos

	def __hash__(self):
		return hash(self.pos)

	def __str__(self):
		return "tile(pos{}, g_score({}), h_score({}), f_score({}))".format(self.pos, self.g_score, self.h_score, self.f_score)

	def __repr__(self):
		return "tile(pos{}, g_score({}), h_score({}), f_score({}))".format(self.pos, self.g_score, self.h_score, self.f_score)

	def __getitem__(self, i):
		return self.pos[i]

	def __cmp__(self, other):
		return cmp(self.f_score, other.f_score)

def main():
	game = pacman_map("doublewall_map.pacmap")
	finder = pathfinder(game, heuristic="manhattan")
	finder.find()
	finder_2 = pathfinder(game, heuristic="euclidean")
	finder_2.find()

if __name__ == "__main__":
	main()
