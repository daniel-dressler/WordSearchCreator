class WsGrid < ActiveRecord::Base
  	belongs_to :set, :class_name => 'WordSearchSet'
  	attr_accessor :grid
  	def set(set)
		# todo: auto generate word count
		#todo: automatic resizing in bulk generation */
 		raw_grid = `lib/algo/algo 5 5 #{set.goal.angles} 1 "#{set.words.to_s}" 1 "#{set.swears.to_s}" #{set.prototype.seed}`;
		(height, width, raw_board) = raw_grid.split(/;/)
		if height != set.prototype.height
			set.prototype.set(height, width)
		end
		@grid = []
		for i in (0...height.to_i) do
			@grid[i] = raw_board.slice!(0, width.to_i).split(//)
		end
  	end
	
	def to_a
		@grid
	end
end
