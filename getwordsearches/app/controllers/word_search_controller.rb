
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
end
