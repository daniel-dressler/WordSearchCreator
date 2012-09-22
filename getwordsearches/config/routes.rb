Getwordsearches::Application.routes.draw do

	match "step1(/:id)", :to => "word_search_sets#step1"
	match "step2/:id", :to => "word_search_sets#step2"
  	match "preview/:angles/:words", :to => "word_search_sets#preview"

	root :to => 'landing_page#index'
end
