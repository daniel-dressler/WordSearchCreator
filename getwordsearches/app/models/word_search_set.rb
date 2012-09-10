class WordSearchSet < ActiveRecord::Base
  	has_one :prototype, :class_name => 'WsPrototype'
  	has_one :goal, :class_name => 'WsGoal'
  	has_one :swears, :class_name => 'WsWordList'
  	has_one :words, :class_name => 'WsWordList'
  	has_many :grids, :class_name => 'WsGrid'
  	has_one :alphabet, :class_name => 'WsAlpha'

	def initialize
		super
		self.save
	end
	
	def step0
		@words = build_words
		@prototype = build_prototype
		@goal = build_goal
		@swears = build_swears
		@alphabet = build_alphabet
	end
=begin	
	def save
		super.save
		@words.save
		@swears.save
		@prototype.save
		@goal.save
		@alphabet.save
	end
=end
	
  	def step1(copies)
		@goal.set(copies)
  	end

  	def step2(words, swears)
	 	@words.set(words) 
	 	@swears.set(swears)
  	end

	def press
		@goal.copies.times do
			puts self.grids.inspect	
		end
	end
	
  	def to_a
		[]
	end

  	def to_pdf

  	end
end
