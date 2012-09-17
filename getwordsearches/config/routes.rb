Getwordsearches::Application.routes.draw do
  	resources :word_search_sets

  	match "preview/:angles/:words/:swears", :to => "word_search_sets#preview"

	root :to => 'landing_page#index'
end
