require 'test_helper'

class LandingPageControllerTest < ActionController::TestCase
  test "should get view" do
    get :view
    assert_response :success
  end

end
