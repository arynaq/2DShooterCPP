import numpy
import os 
import random

class pacman_map:

	def __init__(self, custom_map = None):
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

	def __init__(self, pacman_map):
		self._map = pacman_map.map()
		self.open_tiles = []
		self.closed_tiles = []
		self._search_adjacent_tiles()

	def _find_pacman(self):
		return tuple([int(pos) for pos in numpy.where(self._map == 3)])

	def _find_ghost(self):
		return tuple([int(pos) for pos in numpy.where(self._map == 4)])

	def _search_adjacent_tiles(self):
		pos = self._find_ghost()
		up = tuple([pos[0], pos[1] - 1]) if (pos[1] - 1) >= 0 else None
		right = tuple([pos[0] + 1, pos[1]]) if (pos[0] + 1) >= 0 else None
		down =  tuple([pos[0], pos[1] + 1]) if (pos[1] + 1) < self._map.shape[0] else None
		left = tuple([pos[0] - 1, pos[1]]) if (pos[0] - 1) < self._map.shape[1] else None
		adjacent_tiles = [tile((pos)) for pos in [up, right, down, left] if self._map[pos] == 1]
		self.open_tiles.extend(adjacent_tiles)
		self.open_tiles = list(set(self.open_tiles))

class tile:

	def __init__(self, pos, g_score=None, h_score=None, f_score=None):
		self._pos = pos
		self._g_score = g_score
		self._h_score = h_score
		self._f_score = f_score

	def __eq__(self, other):
		return self._pos == other._pos

	def __hash__(self):
		return hash(self._pos)

	def __str__(self):
		return "tile{}".format(self._pos)

	def __repr__(self):
		return "tile{}".format(self._pos)

def main():
	game = pacman_map("nowalls_map.pacmap")
	finder = pathfinder(game)	

if __name__ == "__main__":
	main()