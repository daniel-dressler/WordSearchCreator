
class WordSearchController < ApplicationController
  	def view
  	end

  	def create
	  	@word_selection = WordSelection.new
	  	@word_selection.words = "das" + params["word_selection"]["words"]
	  	@word_selection.save
	  	redirect_to :action => "index"
  	end

  	def new
	  	@word_selection = WordSelection.new
  	end

  	def index
	  	@word_searches = WordSelection.all
  	end

  	def preview
	  	@word_search_set = WordSearchSet.new()
		@word_search_set.step1(1);
	  	@word_search_set.step2(params[:words], params[:swears])
		@word_search_set.save
		@word_search_set.press
	  	render :template => 'word_search/view', :layout => 'basic'
  	end
end
