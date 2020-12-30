#pragma once

#include <inja.hpp>
#include <nlohmann/json.hpp>

using namespace inja;
using json = nlohmann::json;

namespace TemplateBinder {

	class Template {
		public:
			explicit Template() {}

			std::string Render(std::string str_template, std::string json_data) {
				auto data = json::parse(json_data);

				inja::Environment env;
                env.set_trim_blocks(true);
                env.set_lstrip_blocks(true);

				std::string result = env.render(str_template, data);
				return result;
			}

		    /**
		     * Inspect method defines class meta information (methods, properties etc..)
		     * You can define `inspect` method inline or specialize `duk::Inspect` for your class
		     */
		    template <class Inspector>
		    static void inspect(Inspector &i) 
		    {
		        i.construct(&std::make_shared<Template>);
		        i.method("render", &Template::Render);
		    }
	};

}