class WordSearchSet < ActiveRecord::Base
  	has_one :prototype, :class_name => 'WsPrototype'
  	has_one :goal, :class_name => 'WsGoal'
  	has_one :swears, :class_name => 'WsWordList'
  	has_one :words, :class_name => 'WsWordList'
  	has_many :grids, :class_name => 'WsGrid'
  	has_one :alphabet, :class_name => 'WsAlpha'

	def initialize
		super
		@words = build_words
		@prototype = build_prototype
		@goal = build_goal
		@swears = build_swears
		@alphabet = build_alphabet
	end
		
	def save
		super
		@words.save
		@swears.save
		@prototype.save
		@goal.save
		@alphabet.save
	end

  	def step1(copies, angles)
		@goal.set(copies, angles)
  	end

  	def step2(words, swears)
	 	@words.set(words) 
	 	@swears.set(swears)
  	end

	def press
		@prototype.set(5,5)
		@offline_grids = []
		@goal.copies.times do
			goal = self.grids.build()	
			goal.set(self)
			@offline_grids.push goal
		end
	end
	
  	def to_a
		assembled = []
		@offline_grids.each do |grid|
			puts "here"
			assembled.push grid.to_a	
		end
		assembled
	end

  	def to_pdf

  	end
end
